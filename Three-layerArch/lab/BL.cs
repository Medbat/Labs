
using System;
using System.Collections.Generic;

namespace lab
{
    /// <summary>
    /// класс бизесс-логики
    /// работает с изменением данных, а также передает полученные из 
    /// GUI в дата логику для записи/возвращает в GUI полученные из дата
    /// логики записи для вывода
    /// </summary>
    public static class BL
    {
        /// <summary>
        /// Полученный ввод пользователя из ГУЯ передаётся в дата логику для 
        /// записи в БД
        /// </summary>
        /// <param name="newEntity"></param>
        public static void SendToCreate(Entity newEntity)
        {
                DL.Create(newEntity);
        }

        /// <summary>
        /// получает список записей
        /// </summary>
        /// <returns></returns>
        public static List<Entity> GetEntities()
        {
            return DL.Read();
        }

        /// <summary>
        /// изменяет выбранную запись. id не требуется на вход, так как
        /// он уже содержится в принимаемой записи
        /// </summary>
        /// <param name="newEntity"></param>
        public static void Сhange(Entity newEntity)
        {
            var temp = DL.Read();
            temp[newEntity.id - 1] = newEntity;
            DL.Update(temp);
        }

        /// <summary>
        /// сообщает дата логике, что пользователь хочет удалить элемент
        /// с определенным id
        /// </summary>
        /// <param name="num"></param>
        public static void ToDelete(int num)
        {
            DL.Delete(num);
        }

        /// <summary>
        /// смещает id всех записей начиная с номера n на единицу назад,
        /// используется после удаления
        /// </summary>
        /// <param name="l"></param>
        /// <param name="n"></param>
        public static void Shl(List<Entity> l, int n)
        {
            for (int i = n; i < l.Count; i++)
                l[i].id--;
        }

        public static List<Entity> Solve(out decimal sum)
        {
            List<Entity> entities = DL.Read();
            for (int i = 0; i < entities.Count; i++)
            {
                DateTime dt = new DateTime(entities[i].date.Year, 
                    entities[i].date.Month,
                    1, 0, 0, 0);
                DateTime dt1 = new DateTime(Program.GUIForm.datePicker.Value.Year,
                    Program.GUIForm.datePicker.Value.Month,
                    1, 0, 0, 0);
                switch (entities[i].term)
                {
                    case "месяц":
                        dt = dt.AddMonths(1);
                        break;
                    case "3 месяца":
                        dt = dt.AddMonths(3);
                        break;
                    case "6 месяцев":
                        dt = dt.AddMonths(6);
                        break;
                    case "9 месяцев":
                        dt = dt.AddMonths(9);
                        break;
                    case "год":
                        dt = dt.AddYears(1);
                        break;
                    case "более года":
                        dt = dt.AddMonths(13);
                        break;
                }

                if (entities[i].term == "более года" &&
                    dt > dt1)
                {
                    entities.RemoveAt(i--);
                    continue;
                }
                if (entities[i].term == "более года" && dt <= dt1)
                    continue;
                if (dt != dt1 &&
                    entities[i].term != "более года")
                    entities.RemoveAt(i--);
                
            }

            sum = 0;
            foreach (var entity in entities)
                sum += Count(entity.sum, entity.term);
            
            
            return entities;
        }


        /// <summary>
        /// константные значения процентов для вкладов на
        /// месяц, 3, 6, 9, год, более года соответственно
        /// </summary>
        private static readonly decimal[] percent = 
        { 4.2m, 5.2m, 6.2m, 7.3m, 8.6m, 12m };

        /// <summary>
        /// вычисление отдаваемых денег в зависимости от суммы вклада и срока
        /// </summary>
        /// <param name="a"></param>
        /// <param name="term"></param>
        /// <returns></returns>
        public static decimal Count(decimal a, string term)
        {
            int i = 0;
            switch (term)
            {
                case "месяц":
                    i = 0;
                    break;
                case "3 месяца":
                    i = 1;
                    break;
                case "6 месяцев":
                    i = 2;
                    break;
                case "9 месяцев":
                    i = 3;
                    break;
                case "год":
                    i = 4;
                    break;
                case "больше года":
                    i = 5;
                    break;
            }
            return a + a * percent[i] / 100;
        }
    }
}
