namespace AirDetect
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.DataPoint dataPoint1 = new System.Windows.Forms.DataVisualization.Charting.DataPoint(10D, 0D);
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label_himi = new System.Windows.Forms.Label();
            this.label_PM2_5 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lbAnalogMeter2 = new LBSoft.IndustrialCtrls.Meters.LBAnalogMeter();
            this.label_temp = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.lbKnob1 = new LBSoft.IndustrialCtrls.Knobs.LBKnob();
            this.lbAnalogMeter1 = new LBSoft.IndustrialCtrls.Meters.LBAnalogMeter();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.chart_PM2_5 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.chart_temp = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.chart_himi = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.button_settime = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.checkBox_continue = new System.Windows.Forms.CheckBox();
            this.textBox_interval = new System.Windows.Forms.TextBox();
            this.button_read = new System.Windows.Forms.Button();
            this.button_open = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox_Com = new System.Windows.Forms.ComboBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.textBox_ssid = new System.Windows.Forms.TextBox();
            this.textBox_password = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart_PM2_5)).BeginInit();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart_temp)).BeginInit();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart_himi)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label_himi);
            this.groupBox1.Controls.Add(this.label_PM2_5);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.lbAnalogMeter2);
            this.groupBox1.Controls.Add(this.label_temp);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.lbKnob1);
            this.groupBox1.Controls.Add(this.lbAnalogMeter1);
            this.groupBox1.Location = new System.Drawing.Point(3, 143);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(827, 217);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "实时数据";
            // 
            // label_himi
            // 
            this.label_himi.AutoSize = true;
            this.label_himi.BackColor = System.Drawing.Color.Transparent;
            this.label_himi.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label_himi.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_himi.ForeColor = System.Drawing.Color.White;
            this.label_himi.Location = new System.Drawing.Point(649, 163);
            this.label_himi.Name = "label_himi";
            this.label_himi.Size = new System.Drawing.Size(68, 25);
            this.label_himi.TabIndex = 12;
            this.label_himi.Text = "03.4";
            // 
            // label_PM2_5
            // 
            this.label_PM2_5.AutoSize = true;
            this.label_PM2_5.BackColor = System.Drawing.Color.Transparent;
            this.label_PM2_5.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label_PM2_5.Font = new System.Drawing.Font("宋体", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_PM2_5.ForeColor = System.Drawing.Color.White;
            this.label_PM2_5.Location = new System.Drawing.Point(376, 103);
            this.label_PM2_5.Name = "label_PM2_5";
            this.label_PM2_5.Size = new System.Drawing.Size(80, 40);
            this.label_PM2_5.TabIndex = 11;
            this.label_PM2_5.Text = "034";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(639, 19);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(73, 20);
            this.label5.TabIndex = 10;
            this.label5.Text = "湿度/%";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(122, 19);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(83, 20);
            this.label4.TabIndex = 9;
            this.label4.Text = "温度/℃";
            // 
            // lbAnalogMeter2
            // 
            this.lbAnalogMeter2.BackColor = System.Drawing.Color.Transparent;
            this.lbAnalogMeter2.BodyColor = System.Drawing.Color.LightSeaGreen;
            this.lbAnalogMeter2.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbAnalogMeter2.Location = new System.Drawing.Point(591, 44);
            this.lbAnalogMeter2.MaxValue = 100D;
            this.lbAnalogMeter2.MeterStyle = LBSoft.IndustrialCtrls.Meters.LBAnalogMeter.AnalogMeterStyle.Circular;
            this.lbAnalogMeter2.MinValue = 0D;
            this.lbAnalogMeter2.Name = "lbAnalogMeter2";
            this.lbAnalogMeter2.NeedleColor = System.Drawing.Color.Yellow;
            this.lbAnalogMeter2.Renderer = null;
            this.lbAnalogMeter2.ScaleColor = System.Drawing.Color.White;
            this.lbAnalogMeter2.ScaleDivisions = 10;
            this.lbAnalogMeter2.ScaleSubDivisions = 10;
            this.lbAnalogMeter2.Size = new System.Drawing.Size(165, 165);
            this.lbAnalogMeter2.TabIndex = 7;
            this.lbAnalogMeter2.Value = 0D;
            this.lbAnalogMeter2.ViewGlass = true;
            // 
            // label_temp
            // 
            this.label_temp.AutoSize = true;
            this.label_temp.BackColor = System.Drawing.Color.Transparent;
            this.label_temp.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.label_temp.Font = new System.Drawing.Font("宋体", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label_temp.ForeColor = System.Drawing.Color.White;
            this.label_temp.Location = new System.Drawing.Point(134, 166);
            this.label_temp.Name = "label_temp";
            this.label_temp.Size = new System.Drawing.Size(82, 25);
            this.label_temp.TabIndex = 4;
            this.label_temp.Text = "-12.4";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(346, 19);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(141, 20);
            this.label3.TabIndex = 0;
            this.label3.Text = "PM2.5(ug/m3)";
            // 
            // lbKnob1
            // 
            this.lbKnob1.BackColor = System.Drawing.Color.Transparent;
            this.lbKnob1.DrawRatio = 0.825F;
            this.lbKnob1.IndicatorColor = System.Drawing.Color.Transparent;
            this.lbKnob1.IndicatorOffset = 0F;
            this.lbKnob1.KnobCenter = ((System.Drawing.PointF)(resources.GetObject("lbKnob1.KnobCenter")));
            this.lbKnob1.KnobColor = System.Drawing.Color.White;
            this.lbKnob1.KnobRect = ((System.Drawing.RectangleF)(resources.GetObject("lbKnob1.KnobRect")));
            this.lbKnob1.Location = new System.Drawing.Point(331, 43);
            this.lbKnob1.MaxValue = 1000F;
            this.lbKnob1.MinValue = 0F;
            this.lbKnob1.Name = "lbKnob1";
            this.lbKnob1.Renderer = null;
            this.lbKnob1.ScaleColor = System.Drawing.Color.Lime;
            this.lbKnob1.Size = new System.Drawing.Size(165, 165);
            this.lbKnob1.StepValue = 1F;
            this.lbKnob1.Style = LBSoft.IndustrialCtrls.Knobs.LBKnob.KnobStyle.Circular;
            this.lbKnob1.TabIndex = 8;
            this.lbKnob1.Tag = "";
            this.lbKnob1.Value = -1F;
            // 
            // lbAnalogMeter1
            // 
            this.lbAnalogMeter1.BackColor = System.Drawing.Color.Transparent;
            this.lbAnalogMeter1.BodyColor = System.Drawing.Color.LightSeaGreen;
            this.lbAnalogMeter1.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbAnalogMeter1.Location = new System.Drawing.Point(80, 46);
            this.lbAnalogMeter1.MaxValue = 85D;
            this.lbAnalogMeter1.MeterStyle = LBSoft.IndustrialCtrls.Meters.LBAnalogMeter.AnalogMeterStyle.Circular;
            this.lbAnalogMeter1.MinValue = -20D;
            this.lbAnalogMeter1.Name = "lbAnalogMeter1";
            this.lbAnalogMeter1.NeedleColor = System.Drawing.Color.Yellow;
            this.lbAnalogMeter1.Renderer = null;
            this.lbAnalogMeter1.ScaleColor = System.Drawing.Color.White;
            this.lbAnalogMeter1.ScaleDivisions = 10;
            this.lbAnalogMeter1.ScaleSubDivisions = 10;
            this.lbAnalogMeter1.Size = new System.Drawing.Size(165, 165);
            this.lbAnalogMeter1.TabIndex = 6;
            this.lbAnalogMeter1.Value = 0D;
            this.lbAnalogMeter1.ViewGlass = true;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.tabControl1);
            this.groupBox2.Location = new System.Drawing.Point(3, 366);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(827, 266);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "实时曲线";
            // 
            // tabControl1
            // 
            this.tabControl1.Alignment = System.Windows.Forms.TabAlignment.Left;
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Controls.Add(this.tabPage3);
            this.tabControl1.Location = new System.Drawing.Point(9, 18);
            this.tabControl1.Multiline = true;
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(814, 242);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.chart_PM2_5);
            this.tabPage1.Location = new System.Drawing.Point(26, 4);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(784, 234);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "PM2.5";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // chart_PM2_5
            // 
            chartArea1.Name = "ChartArea1";
            this.chart_PM2_5.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chart_PM2_5.Legends.Add(legend1);
            this.chart_PM2_5.Location = new System.Drawing.Point(0, 0);
            this.chart_PM2_5.Name = "chart_PM2_5";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series1.Legend = "Legend1";
            series1.Name = "PM2.5";
            this.chart_PM2_5.Series.Add(series1);
            this.chart_PM2_5.Size = new System.Drawing.Size(784, 237);
            this.chart_PM2_5.TabIndex = 0;
            this.chart_PM2_5.Text = "chart_PM2_5";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.chart_temp);
            this.tabPage2.Location = new System.Drawing.Point(26, 4);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(784, 234);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "温度";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // chart_temp
            // 
            chartArea2.Name = "ChartArea1";
            this.chart_temp.ChartAreas.Add(chartArea2);
            legend2.Name = "Legend1";
            this.chart_temp.Legends.Add(legend2);
            this.chart_temp.Location = new System.Drawing.Point(0, -1);
            this.chart_temp.Name = "chart_temp";
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series2.Legend = "Legend1";
            series2.Name = "PM2.5";
            series2.Points.Add(dataPoint1);
            this.chart_temp.Series.Add(series2);
            this.chart_temp.Size = new System.Drawing.Size(784, 237);
            this.chart_temp.TabIndex = 1;
            this.chart_temp.Text = "chart_temp";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.chart_himi);
            this.tabPage3.Location = new System.Drawing.Point(26, 4);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(784, 234);
            this.tabPage3.TabIndex = 2;
            this.tabPage3.Text = "湿度";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // chart_himi
            // 
            chartArea3.Name = "ChartArea1";
            this.chart_himi.ChartAreas.Add(chartArea3);
            legend3.Name = "Legend1";
            this.chart_himi.Legends.Add(legend3);
            this.chart_himi.Location = new System.Drawing.Point(0, -1);
            this.chart_himi.Name = "chart_himi";
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series3.Legend = "Legend1";
            series3.Name = "Series1";
            this.chart_himi.Series.Add(series3);
            this.chart_himi.Size = new System.Drawing.Size(784, 237);
            this.chart_himi.TabIndex = 1;
            this.chart_himi.Text = "chart_himi";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label2);
            this.groupBox3.Controls.Add(this.checkBox_continue);
            this.groupBox3.Controls.Add(this.textBox_interval);
            this.groupBox3.Controls.Add(this.button_read);
            this.groupBox3.Controls.Add(this.button_open);
            this.groupBox3.Controls.Add(this.label1);
            this.groupBox3.Controls.Add(this.comboBox_Com);
            this.groupBox3.Location = new System.Drawing.Point(3, 13);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(827, 56);
            this.groupBox3.TabIndex = 2;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "端口";
            // 
            // button_settime
            // 
            this.button_settime.Font = new System.Drawing.Font("宋体", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button_settime.Location = new System.Drawing.Point(688, 20);
            this.button_settime.Name = "button_settime";
            this.button_settime.Size = new System.Drawing.Size(116, 35);
            this.button_settime.TabIndex = 7;
            this.button_settime.Text = "设置时钟";
            this.button_settime.UseVisualStyleBackColor = true;
            this.button_settime.Click += new System.EventHandler(this.button1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(678, 27);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 15);
            this.label2.TabIndex = 6;
            this.label2.Text = "秒/次";
            // 
            // checkBox_continue
            // 
            this.checkBox_continue.AutoSize = true;
            this.checkBox_continue.Location = new System.Drawing.Point(527, 27);
            this.checkBox_continue.Name = "checkBox_continue";
            this.checkBox_continue.Size = new System.Drawing.Size(97, 19);
            this.checkBox_continue.TabIndex = 5;
            this.checkBox_continue.Text = "连续读取:";
            this.checkBox_continue.UseVisualStyleBackColor = true;
            this.checkBox_continue.CheckedChanged += new System.EventHandler(this.checkBox_continue_CheckedChanged);
            // 
            // textBox_interval
            // 
            this.textBox_interval.Location = new System.Drawing.Point(630, 22);
            this.textBox_interval.Name = "textBox_interval";
            this.textBox_interval.Size = new System.Drawing.Size(42, 25);
            this.textBox_interval.TabIndex = 4;
            this.textBox_interval.Text = "1";
            this.textBox_interval.TextChanged += new System.EventHandler(this.textBox_interval_TextChanged);
            // 
            // button_read
            // 
            this.button_read.Location = new System.Drawing.Point(729, 21);
            this.button_read.Name = "button_read";
            this.button_read.Size = new System.Drawing.Size(82, 28);
            this.button_read.TabIndex = 3;
            this.button_read.Text = "读取数据";
            this.button_read.UseVisualStyleBackColor = true;
            this.button_read.Click += new System.EventHandler(this.button_read_Click);
            // 
            // button_open
            // 
            this.button_open.Location = new System.Drawing.Point(195, 22);
            this.button_open.Name = "button_open";
            this.button_open.Size = new System.Drawing.Size(82, 26);
            this.button_open.TabIndex = 2;
            this.button_open.Text = "打开";
            this.button_open.UseVisualStyleBackColor = true;
            this.button_open.Click += new System.EventHandler(this.button_open_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "端口号";
            // 
            // comboBox_Com
            // 
            this.comboBox_Com.FormattingEnabled = true;
            this.comboBox_Com.Location = new System.Drawing.Point(67, 24);
            this.comboBox_Com.Name = "comboBox_Com";
            this.comboBox_Com.Size = new System.Drawing.Size(121, 23);
            this.comboBox_Com.TabIndex = 0;
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.button1);
            this.groupBox4.Controls.Add(this.textBox_password);
            this.groupBox4.Controls.Add(this.textBox_ssid);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Controls.Add(this.button_settime);
            this.groupBox4.Location = new System.Drawing.Point(10, 76);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(810, 61);
            this.groupBox4.TabIndex = 3;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "系统设置";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft YaHei Mono", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(24, 25);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(88, 23);
            this.label6.TabIndex = 8;
            this.label6.Text = "WIFI名称";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft YaHei Mono", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(265, 25);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(48, 23);
            this.label7.TabIndex = 9;
            this.label7.Text = "密码";
            // 
            // textBox_ssid
            // 
            this.textBox_ssid.Location = new System.Drawing.Point(119, 24);
            this.textBox_ssid.Name = "textBox_ssid";
            this.textBox_ssid.Size = new System.Drawing.Size(140, 25);
            this.textBox_ssid.TabIndex = 10;
            // 
            // textBox_password
            // 
            this.textBox_password.Location = new System.Drawing.Point(308, 24);
            this.textBox_password.Name = "textBox_password";
            this.textBox_password.Size = new System.Drawing.Size(141, 25);
            this.textBox_password.TabIndex = 11;
            // 
            // button1
            // 
            this.button1.Font = new System.Drawing.Font("Microsoft YaHei Mono", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.button1.Location = new System.Drawing.Point(455, 18);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(116, 37);
            this.button1.TabIndex = 12;
            this.button1.Text = "设置WIFI";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(842, 644);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Form1";
            this.Text = " 空气质量检测仪";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart_PM2_5)).EndInit();
            this.tabPage2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart_temp)).EndInit();
            this.tabPage3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart_himi)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart_PM2_5;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart_temp;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart_himi;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox_Com;
        private System.Windows.Forms.Button button_open;
        private System.Windows.Forms.Button button_read;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.CheckBox checkBox_continue;
        private System.Windows.Forms.TextBox textBox_interval;
        private System.Windows.Forms.Button button_settime;
        private System.Windows.Forms.Label label3;
        private LBSoft.IndustrialCtrls.Meters.LBAnalogMeter lbAnalogMeter2;
        private LBSoft.IndustrialCtrls.Meters.LBAnalogMeter lbAnalogMeter1;
        private System.Windows.Forms.Label label_temp;
        private LBSoft.IndustrialCtrls.Knobs.LBKnob lbKnob1;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label_himi;
        private System.Windows.Forms.Label label_PM2_5;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBox_password;
        private System.Windows.Forms.TextBox textBox_ssid;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;

    }
}

