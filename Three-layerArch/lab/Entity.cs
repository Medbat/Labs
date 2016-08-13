using System;

namespace lab
{
    /// <summary>
    /// класс сущности, используемый повсеместно
    /// </summary>
    public class Entity
    {
        // id элемента
        private int _id;
        // сумма вклада
        private decimal _sum;
        // дата вклада
        private DateTime _date;
        // срок вклада
        private string _term;

        public decimal sum
        {
            get { return _sum; }
            set { _sum = value; }
        }

        public string term
        {
            get { return _term; }
            set { _term = value; }
        }

        public DateTime date
        {
            get { return _date; }
            set { _date = value; }
        }

        public int id
        {
            get { return _id; }
            set { _id = value; }
        }

        // пустой конструктор для XMLSerializer
        public Entity()
        {
        }

        // констркутор для создания элемента, введенного пользователем
        public Entity(decimal sum, DateTime date, string term)
        {
            set(sum, date, term);
        }

        // конструктор, используемый в изменении записи
        public Entity(int id, decimal sum, DateTime date, string term)
        {
            this.id = id;
            set(sum, date, term);
        }

        // метод для сокращения кода (повторяется в конструкторах)
        private void set(decimal sum, DateTime date, string term)
        {
            this.sum = sum;
            this.date = date;
            this.term = term;
        }
    }
}
