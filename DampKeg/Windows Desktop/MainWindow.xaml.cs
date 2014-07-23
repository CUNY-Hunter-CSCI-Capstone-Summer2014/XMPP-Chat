using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DampKeg
{
    public partial class MainWindow : Window
    {

        public MainWindow()
        {
            InitializeComponent();

            
            username_field.Focus();

            /*
            ChatBox newChatBox = new ChatBox();
            newChatBox.Show();

            EditContact newBox = new EditContact();
            newBox.Show();
            */
        }

        private void Login_to_server(object sender, RoutedEventArgs e)
        {
            string usernameToShow = username_field.Text;

            Roster the_roster_window = new Roster(usernameToShow);
            this.Close();
            the_roster_window.Show();
        }


        /// <summary>
        /// Method when username field has something entered, checks if
        /// is valid username format
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void username_field_TextChanged(object sender, TextChangedEventArgs e)
        {
            string u = username_field.Text;
            //username_textfield.Text = u;

            if (Utility.valid_email_address(u) == true)
            {
                Login_button.IsEnabled = true;
            }
            else
            {
                Login_button.IsEnabled = false;
            }



        }

        private void Go_To_Pass(object sender, System.Windows.Input.KeyEventArgs e)
        {
            // TODO: Add event handler implementation here
            if (e.Key == Key.Enter)
            {
                password_field.Focus();
            }
        }

        private void Go_To_Login(object sender, System.Windows.Input.KeyEventArgs e)
        {
            // Focus is on password 
            // Logs in if Login_Button is enabled.
            // Else nothing

            if (Login_button.IsEnabled) {//makes sure you can login in the first place. 
                if (e.Key == Key.Enter)
                {
                    Login_to_server(sender, e);
                }
            }
        }




    } 
}
