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
    /// Interaction logic for Options.xaml
    /// </summary>
    public partial class Options : Window
    {
        public Options()
        {
            InitializeComponent();
        }

        private void enableAwayMins(object sender, System.Windows.RoutedEventArgs e)
        {
            // TODO: Add event handler implementation here.
            //awayMinutes.IsEnabled = true;
        }

        private void disableAwayMinutes(object sender, System.Windows.RoutedEventArgs e)
        {
            // TODO: Add event handler implementation here
            //awayMinutes.IsEnabled = false;
        }
    }
}
