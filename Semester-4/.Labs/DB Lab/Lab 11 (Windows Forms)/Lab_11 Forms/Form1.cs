using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Lab_11_Forms
{
    public partial class signup_form : Form
    {
        public signup_form()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            SqlConnection conn = new SqlConnection("Data Source=DESKTOP-19TDJ6L\\SQLEXPRESS;Initial Catalog=Forms;Integrated Security=True;"); //Connection string
            conn.Open();
            MessageBox.Show("Connection Open");
            SqlCommand cmd;
            string fname = textBox1.Text,
                lname = textBox2.Text,
                em = textBox3.Text,
                pass = textBox4.Text,
                query = "Insert into Signup_Form(firstname, lastname, email, password) values ('" + fname + "', '" + lname + "', '" + em + "', '" + pass + "')";
            cmd = new SqlCommand(query, conn);
            cmd.ExecuteNonQuery();
            cmd.Dispose();
            conn.Close();
            this.Close();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void lastname_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click_2(object sender, EventArgs e)
        {

        }

        private void login_linkLabel_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Login_Form login_Form = new Login_Form();
            login_Form.ShowDialog();
            this.Close();
        }
    }
}
