using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;

namespace AirDetect
{
    public partial class Form1 : Form
    {
        public delegate void MyInvoke(int PM2_5_dat, int temp_dat, int himi_dat);

        public static byte[] Comm_DataBuffer = new byte[2000];   //依次存放串口接收到的数据
        public static long Comm_Packet_Index = 0;    //每次收到数据个数，并标志数据应放在全局数组位置的索引
        public static long Comm_Packet_Len = 0;
        public byte Comm_Packet_Fuc = 0;
        bool continue_read = false;
        int time_interval = 1000;

        int cnt = 0;
        int PM2_5, PM1_0, PM10;
        int Temp, Himi;
        List<int> Pm2_5_x = new List<int>();
        List<int> Pm2_5_y = new List<int>();
        List<int> Temp_x = new List<int>();
        List<double> Temp_y = new List<double>();
        List<int> Himi_x = new List<int>();
        List<double> Himi_y = new List<double>();
        public Form1()
        {
            InitializeComponent();
            Control.CheckForIllegalCrossThreadCalls = false;

            label_temp.BackColor = Color.Transparent;
            label_temp.Parent = lbAnalogMeter1;//将pictureBox1设为标签的父控件
            //label_temp.Location = new Point(50, 125);//重新设定标签的位置，这个位置时相对于父控件的左上角
            label_temp.Location = new Point((lbAnalogMeter1.Size.Width - label_temp.Size.Width) / 2, (lbAnalogMeter1.Size.Height - label_temp.Size.Height * 2));

            label_PM2_5.BackColor = Color.Transparent;
            label_PM2_5.Parent = lbKnob1;//将pictureBox1设为标签的父控件
            //label_PM2_5.Location = new Point(45, 60);//重新设定标签的位置，这个位置时相对于父控件的左
            label_PM2_5.Location = new Point((lbKnob1.Size.Width - label_PM2_5.Size.Width) / 2, (lbKnob1.Size.Height - label_PM2_5.Size.Height) / 2);

            label_himi.BackColor = Color.Transparent;
            label_himi.Parent = lbAnalogMeter2;//将pictureBox1设为标签的父控件
            //label_himi.Location = new Point(50, 125);//重新设定标签的位置，这个位置时相对于父控件的左
            label_himi.Location = new Point((lbAnalogMeter2.Size.Width - label_himi.Size.Width) / 2, (lbAnalogMeter2.Size.Height - label_himi.Size.Height*2));

            chart_PM2_5.Legends.Clear();
            chart_himi.Legends.Clear();
            chart_temp.Legends.Clear();

            //for (int i = 0; i < 100; i++)
            //{
            //    x.Add(i);
            //    y.Add(i / 10.0);
            //}
            //chart1.ChartAreas[0].AxisY.Maximum = 10;
            //chart1.ChartAreas[0].AxisY.Minimum  = 0;
            //chart1.Series[0].Points.DataBindXY(x,y);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                string[] ArryPort = SerialPort.GetPortNames();

                comboBox_Com.Items.Clear();
                for (int i = 0; i < ArryPort.Length; i++)
                {
                    comboBox_Com.Items.Add(ArryPort[i]);
                }
                comboBox_Com.SelectedIndex = 0;
            }
            catch
            {
                MessageBox.Show("没有搜索到串口");
            } 
        }

        private void button_open_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == false)
            {
                serialPort1.PortName = comboBox_Com.Text;
                serialPort1.Parity = Parity.None;
                serialPort1.DataBits = 8;
                serialPort1.StopBits = StopBits.One;
                serialPort1.Handshake = Handshake.None;
                serialPort1.RtsEnable = true;
                serialPort1.ReadTimeout = 1000;
                serialPort1.BaudRate = 57600;
                button_open.Text = "关闭";

                serialPort1.Open();

            }
            else
            {
                serialPort1.Close();
                button_open.Text = "打开";
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            byte[] rxbuf = new byte[serialPort1.BytesToRead];
            serialPort1.Read(rxbuf, 0, rxbuf.Length);

            if (rxbuf.Length > 0)//页面3
            {
                for (int i = 0; i < rxbuf.Length; i++)
                {
                    Comm_DataBuffer[Comm_Packet_Index] = rxbuf[i];
                    switch (Comm_Packet_Index)
                    {
                        case 0:
                            if (0x5A == Comm_DataBuffer[Comm_Packet_Index])//地址正确
                                Comm_Packet_Index++;
                            else
                            {
                                Comm_Packet_Index = 0;
                            }
                            break;
                        case 1:
                            if (0xA5 == Comm_DataBuffer[Comm_Packet_Index])//地址正确
                                Comm_Packet_Index++;
                            else
                            {
                                Comm_Packet_Index = 0;
                            }
                            break;
                        case 2:
                            Comm_Packet_Fuc = Comm_DataBuffer[2];
                            if (Comm_Packet_Fuc == 0x02 || Comm_Packet_Fuc == 0x04)
                                Comm_Packet_Index++;
                            else
                                Comm_Packet_Index = 0;
                            break;
                        case 3:
                            Comm_Packet_Len = Comm_DataBuffer[3] + 4;
                            Comm_Packet_Index++;
                            break;
                        default:
                            if (Comm_Packet_Len == (Comm_Packet_Index))
                            {
                                Comm_Packet_Index = 0;
                                ProcessData();
                            }
                            else
                            {
                                Comm_Packet_Index++;
                                if (Comm_Packet_Index > 1000)
                                    Comm_Packet_Index = 0;
                            }
                            break;
                    }
                }
            }
        }
        void UpdateChart(int PM2_5_dat, int temp_dat,int himi_dat)//更新曲线
        {
            cnt++;
            Pm2_5_x.Add(cnt);
            Pm2_5_y.Add(PM2_5_dat);
            chart_PM2_5.ChartAreas[0].AxisY.Maximum = Pm2_5_y.Max() + 5;
            chart_PM2_5.ChartAreas[0].AxisY.Minimum = Pm2_5_y.Min() - 5;
            chart_PM2_5.Series[0].Points.DataBindXY(Pm2_5_x, Pm2_5_y);

            Temp_x.Add(cnt);
            Temp_y.Add(temp_dat/10.0);
            chart_temp.ChartAreas[0].AxisY.Maximum = Temp_y.Max() + 1;
            chart_temp.ChartAreas[0].AxisY.Minimum = Temp_y.Min() - 1;
            chart_temp.Series[0].Points.DataBindXY(Temp_x, Temp_y);

            Himi_x.Add(cnt);
            Himi_y.Add(himi_dat / 10.0);
            chart_himi.ChartAreas[0].AxisY.Maximum = Himi_y.Max() + 1;
            chart_himi.ChartAreas[0].AxisY.Minimum = Himi_y.Min() - 1;
            chart_himi.Series[0].Points.DataBindXY(Himi_x, Himi_y);


        }
        void ProcessData()
        {
            byte sum = 0;
            for (int i = 0; i < Comm_Packet_Len; i++)
            {
                sum += Comm_DataBuffer[i];
            }
            if (sum == Comm_DataBuffer[Comm_Packet_Len])//校验正确
            {
                if (Comm_Packet_Fuc == 0x02)
                {
                    MessageBox.Show("时间设置成功");
                }
                if (Comm_Packet_Fuc == 0x04)
                {
                    PM2_5 = ((Int16)(Comm_DataBuffer[6]) << 8) + Comm_DataBuffer[7];
                    Temp = ((Int16)(Comm_DataBuffer[10]) << 8) + Comm_DataBuffer[11];
                    Himi = ((Int16)(Comm_DataBuffer[12]) << 8) + Comm_DataBuffer[13];

                    label_temp.Text = (Temp/10.0).ToString("#00.0");
                    lbAnalogMeter1.Value = Temp / 10.0;
                    label_temp.Location = new Point((lbAnalogMeter1.Size.Width - label_temp.Size.Width) / 2, (lbAnalogMeter1.Size.Height - label_temp.Size.Height*2));

                    label_himi.Text = (Himi / 10.0).ToString("#00.0");
                    lbAnalogMeter2.Value = Himi / 10.0;
                    label_himi.Location = new Point((lbAnalogMeter2.Size.Width - label_himi.Size.Width) / 2, (lbAnalogMeter2.Size.Height - label_himi.Size.Height * 2));

                    label_PM2_5.Text = PM2_5.ToString("#000");
                    label_PM2_5.Location = new Point((lbKnob1.Size.Width - label_PM2_5.Size.Width) / 2, (lbKnob1.Size.Height - label_PM2_5.Size.Height) / 2);
                    if (PM2_5 < 50)
                    {
                        label_PM2_5.ForeColor = Color.Lime;
                        lbKnob1.ScaleColor = Color.Lime;
                    }
                    else if (PM2_5 < 100)
                    {
                        label_PM2_5.ForeColor = Color.Yellow;
                        lbKnob1.ScaleColor = Color.Yellow;
                    }
                    else if (PM2_5 < 150)
                    {
                        label_PM2_5.ForeColor = Color.Orange;
                        lbKnob1.ScaleColor = Color.Orange;
                    }
                    else if (PM2_5 < 200)
                    {
                        label_PM2_5.ForeColor = Color.Blue;
                        lbKnob1.ScaleColor = Color.Blue;
                    }
                    else
                    {
                        label_PM2_5.ForeColor = Color.Red;
                        lbKnob1.ScaleColor = Color.Red;
                    }
                    try
                    {
                        MyInvoke mi = new MyInvoke(UpdateChart);
                        this.BeginInvoke(mi, new Object[] { PM2_5, Temp, Himi });//委托
                    }
                    catch
                    {
                        return;
                    }
                }
            }
        }
        void SendReadCmd()
        {
            byte[] sendbuf = { 0x5A, 0xA5, 0x03, 0x01, 0x01, 0x04 };
            serialPort1.Write(sendbuf,0,6);
        }
        private void button_read_Click(object sender, EventArgs e)
        {
            if (continue_read == true)
            {
                timer1.Interval = time_interval;
                
                if (button_read.Text == "读取中")
                {
                    timer1.Enabled = false;
                    button_read.Text = "读取数据";
                    button_settime.Enabled = true;
                }
                else
                {
                    timer1.Enabled = true;
                    button_read.Text = "读取中";
                    button_settime.Enabled = false;
                }
            }
            else
            {
                SendReadCmd();
            }
        }

        private void checkBox_continue_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox_continue.Checked) continue_read = true;
            else continue_read = false;
        }

        private void textBox_interval_TextChanged(object sender, EventArgs e)
        {
            try
            {
                time_interval = int.Parse(textBox_interval.Text.Trim());
                time_interval = time_interval * 1000;
                if (time_interval <= 0)
                {
                    MessageBox.Show("间隔不能小于1");
                }
            }
            catch
            {
                MessageBox.Show("数据错误");
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            SendReadCmd();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DateTime dt = DateTime.Now;
            byte[] sendbuf = { 0x5A, 0xA5, 0x01, 0x06, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04, 0x01, 0x04 };

            sendbuf[4] = (byte)(dt.Year-2000);
            sendbuf[5] = (byte)(dt.Month);
            sendbuf[6] = (byte)(dt.Day);
            sendbuf[7] = (byte)(dt.Hour);
            sendbuf[8] = (byte)(dt.Minute);
            sendbuf[9] = (byte)(dt.Second);
            sendbuf[10] = 0;
            for (int i = 0; i < 10; i++)
            {
                sendbuf[10] += sendbuf[i];
            }
            serialPort1.Write(sendbuf, 0, 11); 
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            byte[] sendbuf = new byte[100];

            sendbuf[0] = 0x5A;
            sendbuf[1] = 0xA5;
            sendbuf[2] = 0x05;
            
            byte[] ssid = System.Text.Encoding.ASCII.GetBytes(textBox_ssid.Text);
            int j = 0;
            for (int i = 0; i < ssid.Length; i++,j++)
            {
                sendbuf[4 + j] = ssid[i];
            }
            sendbuf[4 + j] = 0;
            j++;
            byte[] password = System.Text.Encoding.ASCII.GetBytes(textBox_password.Text);
            for (int i = 0; i < password.Length; i++, j++)
            {
                sendbuf[4 + j] = password[i];
            }
            sendbuf[3] = (byte)(1 + j);
            sendbuf[4 + j] = 0;
            sendbuf[5 + j] = 0;
            for (int i = 0; i < 5 + j; i++)
            {
                sendbuf[5 + j] += sendbuf[i];
            }
            serialPort1.Write(sendbuf, 0, 6 + j); 
        }

    }
}
