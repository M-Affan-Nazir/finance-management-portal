using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;


namespace PERSONAL_FINANCE_MANAGEMENT_SYSTEM___VISUALIZER
{
    public partial class formMain : Form
    {

        string accountBalance = "./financial_data/accountBalance.fmd";
        string efBalance = "./financial_data/emf.fmd";
        string transacHist = "./financial_data/th.fmd";
        string balanceHist = "./financial_data/bh.fmd";
        string emfHistory = "./financial_data/efh.fmd";

        public formMain()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {   
            double w = Screen.PrimaryScreen.Bounds.Width * 0.8;
            double h = Screen.PrimaryScreen.Bounds.Height * 0.8;
            this.Location = new Point(Convert.ToInt32(w *0.1), Convert.ToInt32(h*0.1));
            this.Size =  new Size(Convert.ToInt32(w), Convert.ToInt32(h));
            this.MinimumSize = new Size(Convert.ToInt32(w), Convert.ToInt32(h));
            this.MaximumSize = new Size(Convert.ToInt32(w), Convert.ToInt32(h));
            Main();
            
        }

        void Main()
        {
            try
            {
                emfBalance.Text = readEMF();
                currentBalance.Text = readAccountBalance();
                interMediate();
            }
            catch
            {

            }
        }

        string readAccountBalance()
        {
            FileStream fs = new FileStream(accountBalance, FileMode.Open);
            BinaryReader br = new BinaryReader(fs);
            int data = br.ReadInt32();
            string currentBalance = "$" + data.ToString();
            fs.Close();
            br.Close();
            return currentBalance;
        }

        string readEMF()
        {
            FileStream fs = new FileStream(efBalance, FileMode.Open);
            BinaryReader br = new BinaryReader(fs);
            int data = br.ReadInt32();
            string emfBalance = "$" +data.ToString();
            fs.Close();
            br.Close();
            return emfBalance;
        }
    
        string[] readTransactionHistory()
        {
            FileStream fs = new FileStream(transacHist, FileMode.Open, FileAccess.Read);
            BinaryReader br = new BinaryReader(fs);
            int thebyte;
            string transactions = "";
            do
            {
                thebyte = br.Read();
                if(thebyte != 0)
                {
                    char c = ((char)thebyte);
                    transactions = transactions + c;
                }

            }
            while (thebyte != -1);
            string[] ls = transactions.Split(' ');
            fs.Close();
            br.Close();
            return ls;

        }

        string[] readBalanceHistory()
        {
            FileStream fs = new FileStream(balanceHist, FileMode.Open, FileAccess.Read);
            BinaryReader br = new BinaryReader(fs);
            int thebyte;
            
            string history = "";
            do
            {
                thebyte = br.Read();
                if (thebyte != 0)
                {
                    char c = ((char)thebyte);
                    history = history + c;
                }

            }
            while (thebyte != -1);
            string[] ls = history.Split(' ');
            fs.Close();
            br.Close();
            return ls;
        }

        void readEmfHistory()
        {
            FileStream fs = new FileStream(emfHistory, FileMode.Open, FileAccess.Read);
            BinaryReader br = new BinaryReader(fs, Encoding.ASCII);
            int thebyte;

            string history = "";
            do
            {
                thebyte = br.Read();
                if (thebyte != 0)
                {
                    char c = ((char)thebyte);
                    history = history + c;
                }

            }
            while (thebyte != -1);
            string[] ls = history.Split(' ');
            fs.Close();
            br.Close();
        }

        //TO CHART

        void readDataIntoChart(string[] history)
        {
            balance1.Titles.Add("Account Balance History");
            balance1.ChartAreas[0].AxisY.Title = "$ Balance";
            balance1.ChartAreas[0].AxisX.Title = "Date";

            for(int i = 0; i < history.Length -1; i++)
            {
                string[] point = history[i].Split('-');
                string epochTime = point[1];
                long epochT = Convert.ToUInt32(epochTime);
                string balanceTotal = point[0];
                DateTimeOffset dateTimeOffset2 = DateTimeOffset.FromUnixTimeSeconds(epochT);
                string year = DateTime.Parse(dateTimeOffset2.ToString()).Year.ToString();
                string month = DateTime.Parse(dateTimeOffset2.ToString()).ToShortDateString().ToString();
                string x = DateTime.Parse(dateTimeOffset2.ToString()).ToOADate().ToString();
                balance1.Series["Balance"].Points.AddXY(month, balanceTotal);
            }
           
        }

        void readTransHisIntoChart(string[] history)
        {
            tranHis1.Series[0].Points.Clear();
            tranHis1.Series[1].Points.Clear();
            tranHis1.Series[2].Points.Clear();
            tranHis1.Series[3].Points.Clear();
            tranHis1.Series[4].Points.Clear();
            tranHis1.Series[5].Points.Clear();

            int food = 0;
            int bills = 0;
            int transportation = 0;
            int necessity = 0;
            int leisure = 0;
            int emergency = 0;
            tranHis1.Titles.Add("Spending Habbit Summary");

            tranHis1.ChartAreas[0].AxisY.Title = "Total $ Spent";

            for (int i = 0; i < history.Length - 1; i++)
            {
                string[] points = history[i].Split('-');
                if (points[0] == "wd")
                {
                    string reason = points[3];
                    int amount = Convert.ToInt32(points[1]);
                    if(reason == "fd")
                    {
                        food += amount;
                    }
                    else if ( reason == "bl")
                    {
                        bills += amount;
                    }
                    else if (reason == "tp")
                    {
                        transportation += amount;
                    }
                    else if (reason == "ns")
                    {
                        necessity += amount;
                    }
                    else if (reason == "ls")
                    {
                        leisure += amount;
                    }
                    else if (reason == "em")
                    {
                        emergency += amount;
                    }

                }
            };
            tranHis1.Series["Food"].Points.AddXY("Spending Type", food);
            tranHis1.Series["Bills / Rent"].Points.AddXY("Spending Type", bills);
            tranHis1.Series["Transport"].Points.AddXY("Spending Type", transportation);
            tranHis1.Series["Necessity"].Points.AddXY("Spending Type", necessity);
            tranHis1.Series["Leisure"].Points.AddXY("Spending Type", leisure);
            tranHis1.Series["Emergency"].Points.AddXY("Spending Type", emergency);
        }

        void readTransHisIntoChart2(string[] history)
        {
            tranHis2.Series[0].Points.Clear();
            tranHis2.Series[1].Points.Clear();
            tranHis2.Series[2].Points.Clear();
            tranHis2.Series[3].Points.Clear();
            tranHis2.Series[4].Points.Clear();
            tranHis2.Series[5].Points.Clear();
            tranHis2.Titles.Add("Spending Trend");

            tranHis2.ChartAreas[0].AxisY.Title = "$ Spent";

            for (int i = 0; i < history.Length - 1; i++)
            {
                string[] points = history[i].Split('-');
                if (points[0] == "wd")
                {
                    string reason = points[3];
                    int time = Convert.ToInt32(points[2]);
                    DateTimeOffset dateTimeOffset2 = DateTimeOffset.FromUnixTimeSeconds(time);
                    string theDate = DateTime.Parse(dateTimeOffset2.ToString()).ToShortDateString().ToString();

                    int amount = Convert.ToInt32(points[1]);
                    if (reason == "fd")
                    {
                        tranHis2.Series["Food"].Points.AddXY(theDate, amount);
                       
                    }
                    else if (reason == "bl")
                    {
                        tranHis2.Series["Bills / Rent"].Points.AddXY(theDate, amount);
                        
                    }
                    else if (reason == "tp")
                    {
                        
                        tranHis2.Series["Transport"].Points.AddXY(theDate, amount);
                    }
                    else if (reason == "ns")
                    {
                        tranHis2.Series["Necessity"].Points.AddXY(theDate, amount);
                        
                    }
                    else if (reason == "ls")
                    {
                        tranHis2.Series["Leisure"].Points.AddXY(theDate, amount);
                        
                    }
                    else if (reason == "em")
                    {
                        tranHis2.Series["Emergency"].Points.AddXY(theDate, amount);
                       
                    }

                }
            };
        }

        void interMediate()
        {
            string[] balanceHistory = readBalanceHistory();
            if(balanceHistory.Length > 100)
            {
                var filteredList = new List<string>();
                int maxIndex = balanceHistory.Length - 1;
                int startingIndex = maxIndex - 97;
                for(int i = startingIndex; i< maxIndex; i++)
                {
                    filteredList.Add(balanceHistory[i]);
                }
                readDataIntoChart(filteredList.ToArray());
            }
            else
            {
                readDataIntoChart(readBalanceHistory());
            }

            string[] transactionHistory = readTransactionHistory();
            if (transactionHistory.Length > 100)
            {
                var filteredList2 = new List<string>();
                int maxIndex2 = transactionHistory.Length - 1;
                int startingIndex2 = maxIndex2 - 97;
                for (int i = startingIndex2; i < maxIndex2; i++)
                {
                    filteredList2.Add(transactionHistory[i]);
                }
                readTransHisIntoChart(filteredList2.ToArray());
                readTransHisIntoChart2(filteredList2.ToArray());
            }
            else
            {
                readTransHisIntoChart(readTransactionHistory());
                readTransHisIntoChart2(readTransactionHistory());
            }

        }

    }

}