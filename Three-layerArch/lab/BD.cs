using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;

namespace lab
{
    /// <summary>
    /// класс самого нижнего уровня - базы данных.
    /// предоставляет доступ к xml-файлу классу дата логики
    /// </summary>
    public static class BD
    {
        /// <summary>
        /// сам сериализатор. используется в дата логике
        /// </summary>
        public static readonly XmlSerializer MySerializer = 
            new XmlSerializer(typeof(List<Entity>));

        /// <summary>
        /// свойство, при чтении которого геттер возвращает новую ссылку на поток
        /// для записи. поток должен быть закрыт после использования, иначе повторное
        /// открытие файла не может быть произведено
        /// </summary>
        public static StreamWriter MyStreamWriter
        {
            get
            {
                return new 
                    StreamWriter("database.xml");
            }
            set { MyStreamWriter = value; }
        }

        /// <summary>
        /// свойство, при чтении которого геттер возвращает новую ссылку на поток
        /// для чтения. поток должен быть закрыт после использования, иначе повторное
        /// открытие файла не может быть произведено
        /// </summary>
        public static FileStream MyFileStream
        {
            get
            {
                return new 
                    FileStream("database.xml", FileMode.Open);
            }
            set { MyFileStream = value; }
        }
    }
}
