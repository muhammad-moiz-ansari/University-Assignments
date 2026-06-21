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
using System.Collections;

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

        }

        private void createButton_Click(object sender, EventArgs e)
        {
            SqlConnection conn = new SqlConnection("Data Source=DESKTOP-19TDJ6L\\SQLEXPRESS;Initial Catalog=Forms;Integrated Security=True;"); //Connection string
            conn.Open();
            SqlCommand cmd, cmd2;
            string id = textBox1.Text,
                //pass = textBox3.Text,
                query2 = "SELECT count(*) FROM Users u WHERE u.userid = " + id;
            cmd2 = new SqlCommand(query2, conn);
            int res = (int)cmd2.ExecuteScalar();
            if (res > 0)
            {
                MessageBox.Show("ID already exists", "Validation Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            string //id = textBox1.Text,
                name = textBox2.Text,
                un = textBox3.Text,
                pass = textBox4.Text,
                query = "Insert into Users(userid, name, username, password) values ('" + id + "', '" + name + "', '" + un + "', '" + pass + "')";
            cmd = new SqlCommand(query, conn);
            cmd.ExecuteNonQuery();
            cmd.Dispose();
            conn.Close();

            MessageBox.Show("User added!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        private void readButton_Click(object sender, EventArgs e)
        {
            read_data();
        }

        private void read_data()
        {
            dataGridView.Rows.Clear();
            backButton.Visible=true;
            signuppanel.Visible=false;
            dataGridView.Visible=true;

            using (SqlConnection conn = new SqlConnection("Data Source=DESKTOP-19TDJ6L\\SQLEXPRESS;Initial Catalog=Forms;Integrated Security=True;"))
            {
                conn.Open();
                string query = "SELECT userid, name, username, password FROM Users";
                using (SqlCommand cmd = new SqlCommand(query, conn))
                {
                    using (SqlDataReader reader = cmd.ExecuteReader())
                    {
                        while (reader.Read())
                        {
                            dataGridView.Rows.Add(reader["userid"], reader["name"], reader["username"], reader["password"]);
                        }
                    }
                }
            }
        }

        private void backButton_Click(object sender, EventArgs e)
        {
            backButton.Visible=false;
            signuppanel.Visible=true;
            dataGridView.Visible=false;
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            SqlConnection conn = new SqlConnection("Data Source=DESKTOP-19TDJ6L\\SQLEXPRESS;Initial Catalog=Forms;Integrated Security=True;"); //Connection string
            conn.Open();
            SqlCommand cmd, cmd2;
            string query_del = "TRUNCATE TABLE Users";
            cmd=new SqlCommand(query_del, conn);
            cmd.ExecuteNonQuery();

            foreach (DataGridViewRow row in dataGridView.Rows)
            {
                if (row.IsNewRow) 
                    continue;

                int userid = Convert.ToInt32(row.Cells[0].Value);
                string name = row.Cells[1].Value.ToString();
                string username = row.Cells[2].Value.ToString();
                string password = row.Cells[3].Value.ToString();


                string query = "Insert into Users(userid, name, username, password) values ('" + userid + "', '" + name + "', '" + username + "', '" + password + "')";
                cmd = new SqlCommand(query, conn);
                cmd.ExecuteNonQuery();
            }
            cmd.Dispose();
            conn.Close();

            read_data();
        }

        private void deleteButton_Click(object sender, EventArgs e)
        {
            if (dataGridView.SelectedRows.Count > 0)
            {
                DataGridViewRow selectedRow = dataGridView.SelectedRows[0];

                int userid = Convert.ToInt32(selectedRow.Cells[0].Value);

                using (SqlConnection conn = new SqlConnection("Data Source=DESKTOP-19TDJ6L\\SQLEXPRESS;Initial Catalog=Forms;Integrated Security=True;"))
                {
                    conn.Open();
                    string query = "DELETE FROM Users WHERE userid = @id";
                    using (SqlCommand cmd = new SqlCommand(query, conn))
                    {
                        cmd.Parameters.AddWithValue("@id", userid);
                        cmd.ExecuteNonQuery();
                    }
                }
                read_data();
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            Users_Display display = new Users_Display();
            display.ShowDialog();
        }
    }
}
