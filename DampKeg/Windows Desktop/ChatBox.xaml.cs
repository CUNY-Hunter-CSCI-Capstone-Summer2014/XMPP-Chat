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
    /// Interaction logic for ChatBox.xaml
    /// </summary>
    public partial class ChatBox : Window
    {
        private string ContactName;
        //public StackPanel myStackPanel;
        public ChatBox()
        {
            InitializeComponent();
        }
        public ChatBox(string name)
        {
            ContactName = name;
            this.Focus();
            InputBox.Focus();
            //myStackPanel = new StackPanel();
            InitializeComponent();

        }
       
        private void SendText(object sender, System.Windows.Input.KeyEventArgs e)
        {
        	// TODO: Add event handler implementation here.
            if (e.Key == Key.Enter)
            {
                //string temp = ;
                TextBlock temp = new TextBlock();
                temp.Text = "ME: ";
                temp.Text += InputBox.Text;
                InputBox.Clear();
                ListBoxItem NewEntity = new ListBoxItem();
                NewEntity.Content = temp;
                TextView.Items.Add(NewEntity);            
            }
        }
        
       
    }
}
