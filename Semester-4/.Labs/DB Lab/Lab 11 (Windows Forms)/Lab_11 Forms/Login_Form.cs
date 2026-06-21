using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace Lab_11_Forms
{
    public partial class Login_Form : Form
    {
        public Login_Form()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void login_linkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            signup_form signup = new signup_form();
            signup.ShowDialog();
            this.Close();
        }

        private void signup_button_Click(object sender, EventArgs e)
        {
            SqlConnection conn = new SqlConnection("Data Source=DESKTOP-19TDJ6L\\SQLEXPRESS;Initial Catalog=Forms;Integrated Security=True;"); //Connection string
            conn.Open();
            MessageBox.Show("Connection Open");
            SqlCommand cmd;
            string em = textBox4.Text,
                pass = textBox3.Text,
                query = "SELECT count(*) FROM Signup_Form sf WHERE email = '" + em + "' AND password = '" + pass + "'";
            cmd = new SqlCommand(query, conn);
            int res = (int)cmd.ExecuteScalar();

            if (res == 0)
            {
                MessageBox.Show("Login Failed! :(");
            }
            else
            {
                MessageBox.Show("Login Successfully!!");
            }

            cmd.Dispose();
            conn.Close();
            this.Close();
        }
    }
}
