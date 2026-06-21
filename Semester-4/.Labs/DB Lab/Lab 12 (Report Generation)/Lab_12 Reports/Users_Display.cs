using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_11_Forms
{
    public partial class Users_Display : Form
    {
        public Users_Display()
        {
            InitializeComponent();
            SqlServerTypes.Utilities.LoadNativeAssemblies(AppDomain.CurrentDomain.BaseDirectory);
        }

        private void Users_Display_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'formsDataSet1.Users' table. You can move, or remove it, as needed.
            this.usersTableAdapter.Fill(this.formsDataSet1.Users);

            this.reportViewer1.RefreshReport();
        }

        private void reportViewer1_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
