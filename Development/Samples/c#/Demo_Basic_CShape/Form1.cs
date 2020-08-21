using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Drawing.Imaging;
using System.Windows.Forms;
using MVDAPI.NET;
using System.Runtime.InteropServices;
namespace Demo_Basic_CShape
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            m_nDeviceCurSel = -1;
            m_GrabbingCallback = new PMVD_GRABBING_CALLBACK(GrabbingCallback);
            lpContext = new IntPtr(123); 
        }

        public MVD_DEVICE_INFORMATION[] DeviceInfo;
        MVD_DEVICE_INFORMATION_LIST m_DeviceInformationList;
        int m_nDeviceCurSel;
        PMVD_GRABBING_CALLBACK m_GrabbingCallback;
        IntPtr lpContext;//回调的上下文句柄
        public static unsafe System.Drawing.Bitmap BytesToBitmap(byte *bytes, int width, int height, int nBitCount)
        {
            try
            {
                PixelFormat bitmaptype = PixelFormat.Format8bppIndexed;
                int nPixelBytes = nBitCount >> 3;

                if (3 == nPixelBytes)
                {
                    bitmaptype = PixelFormat.Format24bppRgb;
                }
                else if (4 == nPixelBytes)
                {
                    bitmaptype = PixelFormat.Format32bppPArgb;
                }

                Bitmap bitmap = new Bitmap(width, height, bitmaptype);
                //获取图像的BitmapData对像 
                BitmapData bmpData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.ReadWrite, bitmaptype);

                byte* ptr = (byte*)(bmpData.Scan0);
                int nWidthBytes = width * nPixelBytes;
                int nSrcOffset = 0;
                int nDesOffset = 0;
                for (int i = 0; i < height; i++)
                {
                    nSrcOffset = (height - i - 1) * nWidthBytes;
                    nDesOffset = 0;
                    for (int j = 0; j < width; j++)
                    {
                        for (int k = 0; k < nPixelBytes; k++)
                        {
                            *(ptr + nDesOffset + k) = bytes[nSrcOffset + k];
                        }

                        nDesOffset += nPixelBytes;
                        nSrcOffset += nPixelBytes;
                    }

                    ptr = ptr + nWidthBytes;
                }

                bitmap.UnlockBits(bmpData);  // 解锁内存区域

                if (1 == nPixelBytes)
                {
                    // 修改生成位图的索引表，从伪彩修改为灰度
                    ColorPalette palette;
                    // 获取一个Format8bppIndexed格式图像的Palette对象
                    using (Bitmap bmp = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
                    {
                        palette = bmp.Palette;
                    }
                    for (int i = 0; i < 256; i++)
                    {
                        palette.Entries[i] = Color.FromArgb(i, i, i);
                    }
                    // 修改生成位图的索引表
                    bitmap.Palette = palette;
                }

                return bitmap;
            }
            catch (ArgumentNullException ex)
            {
                throw ex;
            }
            catch (ArgumentException ex)
            {
                throw ex;
            }
        }

        unsafe private void GrabbingCallback(int nDeviceIndex, IntPtr GrabImage, IntPtr GrabImageData, IntPtr lpContext)
        {
            MVD_GRAB_IMAGE grab_image = new MVD_GRAB_IMAGE();
            grab_image = (MVD_GRAB_IMAGE)Marshal.PtrToStructure((IntPtr)((Int64)GrabImage), typeof(MVD_GRAB_IMAGE));
            Thread.Sleep(1);
            byte* pBitmap = (byte*)GrabImageData.ToPointer();
            Bitmap bitmap = BytesToBitmap(pBitmap, grab_image.ImageBaseInfo.nImageWidth, grab_image.ImageBaseInfo.nImageHeight, grab_image.ImageBaseInfo.nImageBitCount);
            pictureBox_DISPLAY.Image = bitmap;
        }

        
        unsafe private void Form1_Load(object sender, EventArgs e)
        {
            int i = 0;

            MVD.Initial(MVD_DEVICE_INTERFACE_TYPE.MVD_DEVICE_INTERFACE_TYPE_UNKNOWN, out m_DeviceInformationList);

            DeviceInfo = new MVD_DEVICE_INFORMATION[m_DeviceInformationList.uiDeviceNum];
            
            for (i = 0; i < m_DeviceInformationList.uiDeviceNum; i++)
            {
                DeviceInfo[i] = (MVD_DEVICE_INFORMATION)Marshal.PtrToStructure((IntPtr)((Int64)m_DeviceInformationList.pDeviceInfo[i]), typeof(MVD_DEVICE_INFORMATION));
                string str = System.Text.Encoding.Default.GetString(DeviceInfo[i].szModelName).TrimEnd('\0');
                str = str.Replace("\0", "");
                string szText = String.Format("Model: {0}, Serial Number: {1}", str, DeviceInfo[i].uiSerialNumber);
                ComboBox_DEVICE_LIST.Items.Insert(i, szText);
            }

            m_nDeviceCurSel = m_DeviceInformationList.uiDeviceNum == 0 ? -1 : 0;
            ComboBox_DEVICE_LIST.SelectedIndex = m_nDeviceCurSel;
            exitEvent = new AutoResetEvent(false);
            Update_Interface_When_Device_Selected();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            MVD.Uninitial();
        }

        private void Update_ListBoxDeviceInfo()
        {
            if (m_nDeviceCurSel == -1) return;
            listBox_DEVICE_INFO.Items.Clear();
            string str;
            str = String.Format("uiDeviceModel = {0}", DeviceInfo[m_nDeviceCurSel].uiDeviceModel);
            listBox_DEVICE_INFO.Items.Add(str);
            str = String.Format("szModelName = {0}", DeviceInfo[m_nDeviceCurSel].szModelName);
            listBox_DEVICE_INFO.Items.Add(str);
            str = String.Format("uiSerialNumber = {0}", DeviceInfo[m_nDeviceCurSel].uiSerialNumber);
            listBox_DEVICE_INFO.Items.Add(str);
            str = String.Format("FirmwareVersion = {0}.{1}", DeviceInfo[m_nDeviceCurSel].FirmwareVersion.ucMajor, DeviceInfo[m_nDeviceCurSel].FirmwareVersion.ucMinor);
            listBox_DEVICE_INFO.Items.Add(str);
            str = String.Format("FpgaVersion = {0}.{1}", DeviceInfo[m_nDeviceCurSel].FpgaVersion.ucMajor, DeviceInfo[m_nDeviceCurSel].FpgaVersion.ucMinor);
            listBox_DEVICE_INFO.Items.Add(str);
        }

        private void Update_Interface_When_Device_Selected()
        {
            if (m_nDeviceCurSel == -1) return;
            Update_ListBoxDeviceInfo();

            bool bOpen = true;
            MVD.GetDeviceOpen(m_nDeviceCurSel, ref bOpen);
            checkBox_OPEN_CLOSE_DEVICE.Checked = bOpen;
            checkBox_OPEN_CLOSE_DEVICE.Text = bOpen ? "关闭设备" : "打开设备";
            PMVD_GRABBING_CALLBACK pfCallback = null;
            MVD.GetGrabbingCallback(m_nDeviceCurSel, ref pfCallback, ref lpContext);

            checkBox_START_CALLBACK_GRAB.Enabled = bOpen;
            checkBox_START_GRAB.Enabled = bOpen;
        }

        private void ComboBox_DEVICE_LIST_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_nDeviceCurSel = ComboBox_DEVICE_LIST.SelectedIndex;
            Update_Interface_When_Device_Selected();
        }

        private void checkBox_OPEN_CLOSE_DEVICE_CheckedChanged(object sender, EventArgs e)
        {
            bool bCheck = checkBox_OPEN_CLOSE_DEVICE.Checked;
            int nReturnCode = MVD.SetDeviceOpen(m_nDeviceCurSel, bCheck);
            Update_Interface_When_Device_Selected();
        }

        private void checkBox_START_CALLBACK_GRAB_CheckedChanged(object sender, EventArgs e)
        {
            if (m_nDeviceCurSel == -1) return;
            bool bCheck = checkBox_START_CALLBACK_GRAB.Checked;
            if (bCheck)
            {
                TIMERID_GET_FPS.Start();
                MVD.SetGrabbingStart(m_nDeviceCurSel, true);
                MVD.SetGrabbingCallback(m_nDeviceCurSel, m_GrabbingCallback, pictureBox_DISPLAY.Handle);
            }
            else
            {
                TIMERID_GET_FPS.Stop();
                MVD.SetGrabbingCallback(m_nDeviceCurSel, null, pictureBox_DISPLAY.Handle);
                MVD.SetGrabbingStart(m_nDeviceCurSel, false);
            }

            checkBox_START_CALLBACK_GRAB.Text = bCheck ? "停止回调采集" : "启动回调采集";

            checkBox_START_GRAB.Enabled = !bCheck;
        }

        private void checkBox_START_GRAB_CheckedChanged(object sender, EventArgs e)
        {
            if (m_nDeviceCurSel == -1) return;
            bool bCheck = checkBox_START_GRAB.Checked;
            if (bCheck)
            {
                TIMERID_GET_FPS.Start();
                StartGrabImageThread(true);
            }
            else
            {
                TIMERID_GET_FPS.Stop();
                StartGrabImageThread(false);
            }

            checkBox_START_GRAB.Text = bCheck ? "停止主动采集" : "启动主动采集";

            checkBox_START_CALLBACK_GRAB.Enabled = !bCheck;
        }

        private AutoResetEvent exitEvent;
        private Thread thread;

        private bool StartGrabImageThread(bool bStart)
        {
            if (m_nDeviceCurSel == -1) return false;
            if (bStart)
            {
                thread = new Thread(new ThreadStart(GrabImageThread));
                thread.Start();
            }
            else
            {
                exitEvent.Set();
                thread.Join();
            }
            return true;
        }

        unsafe private void GrabImageThread()
        {
            while (true)
            {
                if (exitEvent.WaitOne(0))
                {
                    
                    break;
                }

                MVD_GRAB_IMAGE grab_image = new MVD_GRAB_IMAGE();
                IntPtr ptr = new IntPtr(3);
                IntPtr pImageData = new IntPtr(4);
                MVD.GrabImage(m_nDeviceCurSel, out ptr, out pImageData);
                byte* pBitmap = (byte*)pImageData.ToPointer();
                grab_image = (MVD_GRAB_IMAGE)Marshal.PtrToStructure((IntPtr)((Int64)ptr), typeof(MVD_GRAB_IMAGE));
                Bitmap bitmap = BytesToBitmap(pBitmap, grab_image.ImageBaseInfo.nImageWidth, grab_image.ImageBaseInfo.nImageHeight, grab_image.ImageBaseInfo.nImageBitCount);
                pictureBox_DISPLAY.Image = bitmap;
            }
        }

        private void button__SETTING_Click(object sender, EventArgs e)
        {
            MVD.OpenSettingPage(m_nDeviceCurSel, lpContext, 0, 0);
        }

        private void TIMERID_GET_FPS_Tick(object sender, EventArgs e)
        {
            float fFps = 0;
            MVD.GetGrabbingFps(m_nDeviceCurSel, ref fFps);
            string rate = string.Format("Grab Fps = {0}", fFps);
            this.Text = rate;
        }
    }
}
