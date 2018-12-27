using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TemperatureDataLoggerAndControl
{
    public partial class Form1 : Form
    {
        /* declaration of global variables */
        byte read_byte1;
        byte read_byte2;
        byte read_byte3;
        byte read_byte4;
        byte read_byte5;
        byte read_status;

        int read1 = 0;
        int read2 = 0;
        int read3 = 0;
        int read4 = 0;
        int read5 = 0;

        public Form1()
        {
            InitializeComponent();
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            serialPort1.Open();
            read_byte1 = 0;
            read_byte2 = 0;
            read_byte3 = 0;
            read_byte4 = 0;
            read_byte5 = 0;
            read_status = 0;

            read_byte1 = (byte)(serialPort1.ReadByte());
            read_byte2 = (byte)(serialPort1.ReadByte());
            read_byte3 = (byte)(serialPort1.ReadByte());
            read_byte4 = (byte)(serialPort1.ReadByte());
            read_byte5 = (byte)(serialPort1.ReadByte());
            read_status = (byte)(serialPort1.ReadByte());

            read1 = read_byte1 - 0x30;
            read2 = read_byte2 - 0x30;
            read3 = read_byte3 - 0x30;
            read4 = read_byte4 - 0x30;
            read5 = read_byte5 - 0x30;

            label2.Text = read1.ToString() + read2.ToString() + "." + read4.ToString() + read5.ToString();

            if (0x01 == (read_status & 0x01))
            {
                //label8.Text = "ON";
                button3.Text = "ON";
                button3.BackColor = Color.Red;
            }
            else
            {
                //label8.Text = "OFF";
                button3.Text = "OFF";
                button3.BackColor = Color.Green;
            }

            if (0x02 == (read_status & 0x02))
            {
                //label6.Text = "ON";
                button2.Text = "ON";
                button2.BackColor = Color.Red;
            }
            else
            {
                //label6.Text = "OFF";
                button2.Text = "OFF";
                button2.BackColor = Color.Green;
            }

            if (0x04 == (read_status & 0x04))
            {
                //label5.Text = "NO";
                button1.Text = "NO";
                button1.BackColor = Color.Red;
            }
            else
            {
                //label5.Text = "YES";
                button1.Text = "YES";
                button1.BackColor = Color.Green;    
            }
            serialPort1.Close();
        }
    }
}
