using System;
using System.Windows.Forms;
using lab.Forms;

namespace lab
{
    public static class Program
    {
        // создаем форму здесь для общего контроля из других форм
        public static GUI GUIForm;
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread] 
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(GUIForm = new GUI());
        }
    }
}
