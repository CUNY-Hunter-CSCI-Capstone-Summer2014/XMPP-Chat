using System;
using System.Collections.Generic;
using System.Text;
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
    /// Interaction logic for Roster.xaml
    /// </summary>
    public partial class Roster : Window
    {
        public Roster()
        {
            this.InitializeComponent();
            // Insert code required on object creation below this point.
        }

        private void RosterWindowDoubleClick(object sender, RoutedEventArgs e)
        {
            if (Roster_Window.SelectedItem != null)
            {
                MessageBox.Show(Roster_Window.SelectedItem.ToString());
            }
        }
        public Roster(string uname)
        {
            this.InitializeComponent();
            Roster_Username.Text = uname;
        }

        private void open_chat_window(object sender, RoutedEventArgs e)
        {

            ChatBox chat_box = new ChatBox();
            chat_box.Show();
        }

        private void Add_Person(object sender, System.Windows.RoutedEventArgs e)
        {
            // TODO: Add event handler implementation here.
            ListBoxItem New_Entity = new ListBoxItem();
            New_Entity.Name = "BOB";
            New_Entity.Content = "BOB";
            Roster_Window.Items.Add(New_Entity);
        }

        private void Remove_Person(object sender, System.Windows.RoutedEventArgs e)
        {
            // TODO: Add event handler implementation here.
            for (int i = Roster_Window.SelectedItems.Count - 1; i >= 0; i--)
                Roster_Window.Items.Remove(Roster_Window.SelectedItems[i]);
        }

        private void openOptions(object sender, System.Windows.RoutedEventArgs e)
        {
            // TODO: Add event handler implementation here.
            Options options_box = new Options();
            options_box.ShowDialog();
        }

        private void open_add_contact(object sender, System.Windows.RoutedEventArgs e)
        {
            // TODO: Add event handler implementation here.
            AddContact add_contact = new AddContact();
            add_contact.ShowDialog();

        }

        private void open_chat_window(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
			ChatBox chat_box = new ChatBox();
            chat_box.Show();
        	// TODO: Add event handler implementation here.
        }
    }
}