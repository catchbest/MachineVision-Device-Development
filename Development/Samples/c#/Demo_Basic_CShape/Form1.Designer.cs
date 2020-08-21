namespace Demo_Basic_CShape
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.ComboBox_DEVICE_LIST = new System.Windows.Forms.ComboBox();
            this.pictureBox_DISPLAY = new System.Windows.Forms.PictureBox();
            this.checkBox_OPEN_CLOSE_DEVICE = new System.Windows.Forms.CheckBox();
            this.checkBox_START_CALLBACK_GRAB = new System.Windows.Forms.CheckBox();
            this.checkBox_START_GRAB = new System.Windows.Forms.CheckBox();
            this.button__SETTING = new System.Windows.Forms.Button();
            this.listBox_DEVICE_INFO = new System.Windows.Forms.ListBox();
            this.listBox__TRACE = new System.Windows.Forms.ListBox();
            this.TIMERID_GET_FPS = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_DISPLAY)).BeginInit();
            this.SuspendLayout();
            // 
            // ComboBox_DEVICE_LIST
            // 
            this.ComboBox_DEVICE_LIST.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.ComboBox_DEVICE_LIST.FormattingEnabled = true;
            this.ComboBox_DEVICE_LIST.Location = new System.Drawing.Point(2, 12);
            this.ComboBox_DEVICE_LIST.Name = "ComboBox_DEVICE_LIST";
            this.ComboBox_DEVICE_LIST.Size = new System.Drawing.Size(588, 20);
            this.ComboBox_DEVICE_LIST.TabIndex = 0;
            this.ComboBox_DEVICE_LIST.SelectedIndexChanged += new System.EventHandler(this.ComboBox_DEVICE_LIST_SelectedIndexChanged);
            // 
            // pictureBox_DISPLAY
            // 
            this.pictureBox_DISPLAY.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.pictureBox_DISPLAY.Location = new System.Drawing.Point(2, 38);
            this.pictureBox_DISPLAY.Name = "pictureBox_DISPLAY";
            this.pictureBox_DISPLAY.Size = new System.Drawing.Size(588, 465);
            this.pictureBox_DISPLAY.TabIndex = 1;
            this.pictureBox_DISPLAY.TabStop = false;
            // 
            // checkBox_OPEN_CLOSE_DEVICE
            // 
            this.checkBox_OPEN_CLOSE_DEVICE.Appearance = System.Windows.Forms.Appearance.Button;
            this.checkBox_OPEN_CLOSE_DEVICE.Location = new System.Drawing.Point(631, 148);
            this.checkBox_OPEN_CLOSE_DEVICE.Name = "checkBox_OPEN_CLOSE_DEVICE";
            this.checkBox_OPEN_CLOSE_DEVICE.Size = new System.Drawing.Size(296, 32);
            this.checkBox_OPEN_CLOSE_DEVICE.TabIndex = 4;
            this.checkBox_OPEN_CLOSE_DEVICE.Text = "打开设备";
            this.checkBox_OPEN_CLOSE_DEVICE.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.checkBox_OPEN_CLOSE_DEVICE.UseVisualStyleBackColor = true;
            this.checkBox_OPEN_CLOSE_DEVICE.CheckedChanged += new System.EventHandler(this.checkBox_OPEN_CLOSE_DEVICE_CheckedChanged);
            // 
            // checkBox_START_CALLBACK_GRAB
            // 
            this.checkBox_START_CALLBACK_GRAB.Appearance = System.Windows.Forms.Appearance.Button;
            this.checkBox_START_CALLBACK_GRAB.Location = new System.Drawing.Point(631, 202);
            this.checkBox_START_CALLBACK_GRAB.Name = "checkBox_START_CALLBACK_GRAB";
            this.checkBox_START_CALLBACK_GRAB.Size = new System.Drawing.Size(296, 32);
            this.checkBox_START_CALLBACK_GRAB.TabIndex = 5;
            this.checkBox_START_CALLBACK_GRAB.Text = "启动回调采集";
            this.checkBox_START_CALLBACK_GRAB.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.checkBox_START_CALLBACK_GRAB.UseVisualStyleBackColor = true;
            this.checkBox_START_CALLBACK_GRAB.CheckedChanged += new System.EventHandler(this.checkBox_START_CALLBACK_GRAB_CheckedChanged);
            // 
            // checkBox_START_GRAB
            // 
            this.checkBox_START_GRAB.Appearance = System.Windows.Forms.Appearance.Button;
            this.checkBox_START_GRAB.Location = new System.Drawing.Point(631, 255);
            this.checkBox_START_GRAB.Name = "checkBox_START_GRAB";
            this.checkBox_START_GRAB.Size = new System.Drawing.Size(296, 32);
            this.checkBox_START_GRAB.TabIndex = 6;
            this.checkBox_START_GRAB.Text = "启动主动采集";
            this.checkBox_START_GRAB.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.checkBox_START_GRAB.UseVisualStyleBackColor = true;
            this.checkBox_START_GRAB.CheckedChanged += new System.EventHandler(this.checkBox_START_GRAB_CheckedChanged);
            // 
            // button__SETTING
            // 
            this.button__SETTING.Location = new System.Drawing.Point(631, 439);
            this.button__SETTING.Name = "button__SETTING";
            this.button__SETTING.Size = new System.Drawing.Size(296, 32);
            this.button__SETTING.TabIndex = 7;
            this.button__SETTING.Text = "设置";
            this.button__SETTING.UseVisualStyleBackColor = true;
            this.button__SETTING.Click += new System.EventHandler(this.button__SETTING_Click);
            // 
            // listBox_DEVICE_INFO
            // 
            this.listBox_DEVICE_INFO.FormattingEnabled = true;
            this.listBox_DEVICE_INFO.ItemHeight = 12;
            this.listBox_DEVICE_INFO.Location = new System.Drawing.Point(631, 12);
            this.listBox_DEVICE_INFO.Name = "listBox_DEVICE_INFO";
            this.listBox_DEVICE_INFO.Size = new System.Drawing.Size(296, 124);
            this.listBox_DEVICE_INFO.TabIndex = 8;
            // 
            // listBox__TRACE
            // 
            this.listBox__TRACE.FormattingEnabled = true;
            this.listBox__TRACE.ItemHeight = 12;
            this.listBox__TRACE.Location = new System.Drawing.Point(2, 509);
            this.listBox__TRACE.Name = "listBox__TRACE";
            this.listBox__TRACE.Size = new System.Drawing.Size(925, 100);
            this.listBox__TRACE.TabIndex = 9;
            // 
            // TIMERID_GET_FPS
            // 
            this.TIMERID_GET_FPS.Interval = 2000;
            this.TIMERID_GET_FPS.Tick += new System.EventHandler(this.TIMERID_GET_FPS_Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(954, 616);
            this.Controls.Add(this.listBox__TRACE);
            this.Controls.Add(this.listBox_DEVICE_INFO);
            this.Controls.Add(this.button__SETTING);
            this.Controls.Add(this.checkBox_START_GRAB);
            this.Controls.Add(this.checkBox_START_CALLBACK_GRAB);
            this.Controls.Add(this.checkBox_OPEN_CLOSE_DEVICE);
            this.Controls.Add(this.pictureBox_DISPLAY);
            this.Controls.Add(this.ComboBox_DEVICE_LIST);
            this.Name = "Form1";
            this.Text = "Demo_Basic";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_DISPLAY)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox ComboBox_DEVICE_LIST;
        private System.Windows.Forms.PictureBox pictureBox_DISPLAY;
        private System.Windows.Forms.CheckBox checkBox_OPEN_CLOSE_DEVICE;
        private System.Windows.Forms.CheckBox checkBox_START_CALLBACK_GRAB;
        private System.Windows.Forms.CheckBox checkBox_START_GRAB;
        private System.Windows.Forms.Button button__SETTING;
        private System.Windows.Forms.ListBox listBox_DEVICE_INFO;
        private System.Windows.Forms.ListBox listBox__TRACE;
        private System.Windows.Forms.Timer TIMERID_GET_FPS;

    }
}

