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
using System.Windows.Shapes;

namespace DampKeg
{
    /// <summary>
    /// Interaction logic for AddContact.xaml
    /// </summary>
    public partial class AddContact : Window
    {
        public AddContact()
        {
            InitializeComponent();
			new_contact_field.Focus();
        }

		private void Handle_field_TextChanged(object sender, TextChangedEventArgs e)
        {
            string u = new_contact_field.Text;
            //username_textfield.Text = u;

            if (Utility.valid_email_address(u) == true)
            {
                Add_contact_button.IsEnabled = true;
            }
            else
            {
                Add_contact_button.IsEnabled = false;
            }

        }

		private void Go_To_Nickname(object sender, System.Windows.Input.KeyEventArgs e)
		{
			// TODO: Add event handler implementation here.
			if (e.Key == Key.Enter)
            {
                nickname_field.Focus();
            }
		}

		private void Go_To_Add_Button(object sender, System.Windows.Input.KeyEventArgs e)
		{
			// TODO: Add event handler implementation here.
			if (Add_contact_button.IsEnabled) {//makes sure you can login in the first place. 
                if (e.Key == Key.Enter)
                {
                    New_Contact(sender, e);
                }
            }
		}

		private void New_Contact(object sender, System.Windows.RoutedEventArgs e)
		{
			// TODO: Add event handler implementation here.
			string nicknameToShow = nickname_field.Text;

            //Roster the_roster_window = new Roster(usernameToShow);
            this.Close();
            //the_roster_window.Show();
		}

		
	}

}
