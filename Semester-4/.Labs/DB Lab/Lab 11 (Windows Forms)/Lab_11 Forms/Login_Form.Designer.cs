namespace Lab_11_Forms
{
    partial class Login_Form
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
            System.Windows.Forms.Label header_text;
            this.login_button = new System.Windows.Forms.Button();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.email = new System.Windows.Forms.Label();
            this.password = new System.Windows.Forms.Label();
            this.login_linkLabel = new System.Windows.Forms.LinkLabel();
            this.label1 = new System.Windows.Forms.Label();
            header_text = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // header_text
            // 
            header_text.AutoSize = true;
            header_text.BackColor = System.Drawing.Color.Transparent;
            header_text.Font = new System.Drawing.Font("Showcard Gothic", 22F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            header_text.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            header_text.Location = new System.Drawing.Point(350, 44);
            header_text.Name = "header_text";
            header_text.Size = new System.Drawing.Size(175, 54);
            header_text.TabIndex = 19;
            header_text.Text = "Login!";
            // 
            // login_button
            // 
            this.login_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.login_button.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.login_button.Location = new System.Drawing.Point(388, 310);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(108, 45);
            this.login_button.TabIndex = 18;
            this.login_button.Text = "Login";
            this.login_button.UseVisualStyleBackColor = true;
            this.login_button.Click += new System.EventHandler(this.signup_button_Click);
            // 
            // textBox4
            // 
            this.textBox4.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.textBox4.Font = new System.Drawing.Font("Cascadia Code", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox4.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.textBox4.Location = new System.Drawing.Point(372, 157);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(252, 35);
            this.textBox4.TabIndex = 17;
            // 
            // textBox3
            // 
            this.textBox3.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
            this.textBox3.Font = new System.Drawing.Font("Cascadia Code", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox3.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.textBox3.Location = new System.Drawing.Point(372, 232);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(252, 35);
            this.textBox3.TabIndex = 16;
            // 
            // email
            // 
            this.email.AutoSize = true;
            this.email.BackColor = System.Drawing.Color.Transparent;
            this.email.Font = new System.Drawing.Font("Modern No. 20", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.email.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.email.Location = new System.Drawing.Point(199, 160);
            this.email.Name = "email";
            this.email.Size = new System.Drawing.Size(104, 30);
            this.email.TabIndex = 15;
            this.email.Text = "Email: ";
            // 
            // password
            // 
            this.password.AutoSize = true;
            this.password.BackColor = System.Drawing.Color.Transparent;
            this.password.Font = new System.Drawing.Font("Modern No. 20", 14F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.password.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.password.Location = new System.Drawing.Point(199, 235);
            this.password.Name = "password";
            this.password.Size = new System.Drawing.Size(143, 30);
            this.password.TabIndex = 14;
            this.password.Text = "Password: ";
            // 
            // login_linkLabel
            // 
            this.login_linkLabel.AutoSize = true;
            this.login_linkLabel.BackColor = System.Drawing.Color.Transparent;
            this.login_linkLabel.Font = new System.Drawing.Font("Modern No. 20", 10F);
            this.login_linkLabel.ForeColor = System.Drawing.SystemColors.Highlight;
            this.login_linkLabel.LinkColor = System.Drawing.SystemColors.GradientInactiveCaption;
            this.login_linkLabel.Location = new System.Drawing.Point(493, 375);
            this.login_linkLabel.Name = "login_linkLabel";
            this.login_linkLabel.Size = new System.Drawing.Size(177, 22);
            this.login_linkLabel.TabIndex = 21;
            this.login_linkLabel.TabStop = true;
            this.login_linkLabel.Text = "Create a new account";
            this.login_linkLabel.UseWaitCursor = true;
            this.login_linkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.login_linkLabel_LinkClicked);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Modern No. 20", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(294, 375);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(202, 22);
            this.label1.TabIndex = 20;
            this.label1.Text = "Don\'t have an account? ";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // Login_Form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::Lab_11_Forms.Properties.Resources.Untitled;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ClientSize = new System.Drawing.Size(863, 498);
            this.Controls.Add(this.login_linkLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(header_text);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.email);
            this.Controls.Add(this.password);
            this.DoubleBuffered = true;
            this.Name = "Login_Form";
            this.Text = "LoginForm";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button login_button;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Label email;
        private System.Windows.Forms.Label password;
        private System.Windows.Forms.LinkLabel login_linkLabel;
        private System.Windows.Forms.Label label1;
    }
}