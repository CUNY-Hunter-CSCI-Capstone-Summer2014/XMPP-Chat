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
    /// Interaction logic for EditContact.xaml
    /// </summary>
    public partial class EditContact : Window
    {
        public EditContact()
        {
            InitializeComponent();
        }

        private void GoToLastName(object sender, KeyEventArgs e)
        {
            // TODO: Add event handler implementation here
            if (e.Key == Key.Enter)
            {
                LastNameField.Focus();
            }
        }

        private void GoToEmailField(object sender, KeyEventArgs e)
        {
            // TODO: Add event handler implementation here
            if (e.Key == Key.Enter)
            {
                EmailField.Focus();
            }
        }

        private void EditContactButtonFocus(object sender, KeyEventArgs e)
        {
            // TODO: Add event handler implementation here
            if (e.Key == Key.Enter)
            {
                EditContactButton.Focus();
            }
        }
    }
}
