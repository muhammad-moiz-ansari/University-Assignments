namespace Lab_11_Forms
{
    partial class signup_form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.firstname = new System.Windows.Forms.Label();
            this.lastname = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.password = new System.Windows.Forms.Label();
            this.email = new System.Windows.Forms.Label();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.signup_button = new System.Windows.Forms.Button();
            this.header_text = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.login_linkLabel = new System.Windows.Forms.LinkLabel();
            this.SuspendLayout();
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.textBox1.Font = new System.Drawing.Font("Cascadia Code", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.textBox1.Location = new System.Drawing.Point(328, 134);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(252, 35);
            this.textBox1.TabIndex = 0;
            // 
            // firstname
            // 
            this.firstname.AutoSize = true;
            this.firstname.BackColor = System.Drawing.Color.Transparent;
            this.firstname.Font = new System.Drawing.Font("Modern No. 20", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.firstname.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.firstname.Location = new System.Drawing.Point(155, 137);
            this.firstname.Name = "firstname";
            this.firstname.Size = new System.Drawing.Size(165, 30);
            this.firstname.TabIndex = 1;
            this.firstname.Text = "First Name: ";
            this.firstname.Click += new System.EventHandler(this.label1_Click);
            // 
            // lastname
            // 
            this.lastname.AutoSize = true;
            this.lastname.BackColor = System.Drawing.Color.Transparent;
            this.lastname.Font = new System.Drawing.Font("Modern No. 20", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lastname.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.lastname.Location = new System.Drawing.Point(155, 210);
            this.lastname.Name = "lastname";
            this.lastname.Size = new System.Drawing.Size(159, 30);
            this.lastname.TabIndex = 2;
            this.lastname.Text = "Last Name: ";
            this.lastname.Click += new System.EventHandler(this.lastname_Click);
            // 
            // textBox2
            // 
            this.textBox2.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.textBox2.Font = new System.Drawing.Font("Cascadia Code", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.textBox2.Location = new System.Drawing.Point(328, 207);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(252, 35);
            this.textBox2.TabIndex = 3;
            // 
            // password
            // 
            this.password.AutoSize = true;
            this.password.BackColor = System.Drawing.Color.Transparent;
            this.password.Font = new System.Drawing.Font("Modern No. 20", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.password.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.password.Location = new System.Drawing.Point(155, 362);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(143, 30);
            this.password.TabIndex = 4;
            this.password.Text = "Password: ";
            // 
            // email
            // 
            this.email.AutoSize = true;
            this.email.BackColor = System.Drawing.Color.Transparent;
            this.email.Font = new System.Drawing.Font("Modern No. 20", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.email.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.email.Location = new System.Drawing.Point(155, 287);
            this.email.Name = "email";
            this.email.Size = new System.Drawing.Size(104, 30);
            this.email.TabIndex = 5;
            this.email.Text = "Email: ";
            // 
            // textBox3
            // 
            this.textBox3.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.textBox3.Font = new System.Drawing.Font("Cascadia Code", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.textBox3.Location = new System.Drawing.Point(328, 287);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(252, 35);
            this.textBox3.TabIndex = 6;
            // 
            // textBox4
            // 
            this.textBox4.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.textBox4.Font = new System.Drawing.Font("Cascadia Code", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.textBox4.Location = new System.Drawing.Point(328, 357);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(252, 35);
            this.textBox4.TabIndex = 7;
            // 
            // signup_button
            // 
            this.signup_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.signup_button.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.signup_button.Location = new System.Drawing.Point(344, 428);
            this.signup_button.Name = "signup_button";
            this.signup_button.Size = new System.Drawing.Size(108, 45);
            this.signup_button.TabIndex = 8;
            this.signup_button.Text = "SignUp";
            this.signup_button.UseVisualStyleBackColor = true;
            this.signup_button.Click += new System.EventHandler(this.button1_Click);
            // 
            // header_text
            // 
            this.header_text.AutoSize = true;
            this.header_text.BackColor = System.Drawing.Color.Transparent;
            this.header_text.Font = new System.Drawing.Font("Showcard Gothic", 22F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.header_text.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.header_text.Location = new System.Drawing.Point(321, 41);
            this.header_text.Name = "header_text";
            this.header_text.Size = new System.Drawing.Size(215, 54);
            this.header_text.TabIndex = 9;
            this.header_text.Text = "Sign Up!";
            this.header_text.Click += new System.EventHandler(this.label1_Click_1);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Modern No. 20", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(255, 490);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(220, 22);
            this.label1.TabIndex = 10;
            this.label1.Text = "Already have an account? ";
            this.label1.Click += new System.EventHandler(this.label1_Click_2);
            // 
            // login_linkLabel
            // 
            this.login_linkLabel.AutoSize = true;
            this.login_linkLabel.BackColor = System.Drawing.Color.Transparent;
            this.login_linkLabel.Font = new System.Drawing.Font("Modern No. 20", 10F);
            this.login_linkLabel.ForeColor = System.Drawing.SystemColors.ActiveCaption;
            this.login_linkLabel.LinkColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.login_linkLabel.Location = new System.Drawing.Point(472, 490);
            this.login_linkLabel.Name = "login_linkLabel";
            this.login_linkLabel.Size = new System.Drawing.Size(51, 22);
            this.login_linkLabel.TabIndex = 11;
            this.login_linkLabel.TabStop = true;
            this.login_linkLabel.Text = "login";
            this.login_linkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.login_linkLabel_LinkClicked);
            // 
            // signup_form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.BackgroundImage = global::Lab_11_Forms.Properties.Resources.make_a_normal_pic_into_like_this_one;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(788, 550);
            this.Controls.Add(this.login_linkLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.header_text);
            this.Controls.Add(this.signup_button);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.email);
            this.Controls.Add(this.password);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.lastname);
            this.Controls.Add(this.firstname);
            this.Controls.Add(this.textBox1);
            this.DoubleBuffered = true;
            this.Name = "signup_form";
            this.Text = "SignUp Form";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label firstname;
        private System.Windows.Forms.Label lastname;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Label password;
        private System.Windows.Forms.Label email;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Button signup_button;
        private System.Windows.Forms.Label header_text;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.LinkLabel login_linkLabel;
    }
}

