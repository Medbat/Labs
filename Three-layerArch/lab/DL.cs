using System.Collections.Generic;

using System.IO;

namespace lab
{
    /// <summary>
    /// класс дата логики.
    /// работает напрямую с базой данных, получая из неё ссылки на сериализатор и
    /// потоки чтения/записи.
    /// </summary>
    public static class DL
    {
        /// <summary>
        /// создание записи
        /// </summary>
        /// <param name="newEntity"></param>
        public static void Create(Entity newEntity)
        {
            List<Entity> l = Read();
            StreamWriter myStreamWriter = BD.MyStreamWriter;            
            
            newEntity.id = l.Count + 1;
            l.Add(newEntity);
            BD.MySerializer.Serialize(myStreamWriter, l);
            myStreamWriter.Close();
        }

        /// <summary>
        /// чтение всех записей с помощью сериализатора
        /// </summary>
        /// <returns></returns>
        public static List<Entity> Read()
        {
            List<Entity> l;

            FileStream myFileStream = BD.MyFileStream;
            l = (List<Entity>)BD.MySerializer.Deserialize(myFileStream);
            myFileStream.Close();
            return l;
        }

        /// <summary>
        /// индексатор списка, полученный чтением
        /// </summary>
        /// <param name="i"></param>
        /// <returns></returns>
        public static Entity Read(int i)
        {
            return Read()[i];
        }

        /// <summary>
        /// метод для обновления списка, измененный базнесс-логикой
        /// </summary>
        /// <param name="toWrite"></param>
        public static void Update(List<Entity> toWrite)
        {
            StreamWriter myStreamWriter = BD.MyStreamWriter;
            BD.MySerializer.Serialize(myStreamWriter, toWrite);
            myStreamWriter.Close();
        }

        /// <summary>
        /// удаление элемента
        /// </summary>
        /// <param name="num"></param>
        public static void Delete(int num)
        {
            List<Entity> l = Read();
            l.RemoveAt(num);
            BL.Shl(l, num);

            StreamWriter myStreamWriter = BD.MyStreamWriter;
            BD.MySerializer.Serialize(myStreamWriter, l);
            myStreamWriter.Close();
        }
    }
}
