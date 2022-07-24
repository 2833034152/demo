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

namespace MusicPlayer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        List<string> listSkin = new List<string>();//皮肤集合
        List<string> listPicture = new List<string>();//照片集合
        List<string> listSong = new List<string>(); //存储音乐文件全路径
        private void Form1_Load(object sender, EventArgs e)
        {
            //程序加载时,更换窗体皮肤
            skinEngine1.SkinFile = @"..\..\..\皮肤\skin\MacOS.ssk";
            //初始化照片控件
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;//设置pictureBox中的布局
            pictureBox1.Image = Image.FromFile(@"..\..\..\Images\1353485118249.jpg");    //加载初始图片
            //皮肤文件的全路径,存储至listSkin集合中
            listSkin.AddRange(Directory.GetFiles(@"..\..\..\皮肤\skin", "*.ssk"));
            //照片文件的全路径,存储至listPicture集合中
            listPicture.AddRange(Directory.GetFiles(@"..\..\..\Images", "*.jpg"));
            //取消音乐播放器自动播放功能
            musicPlayer.settings.autoStart = false;
            //URL无法取相对路径,否则报错
            // musicPlayer.URL = @"E:\C#资料\传智播课C#\Project\播放器项目\music\末班车-萧煌奇.mp3";  
            // musicPlayer.URL = Path.GetFullPath(@"..\..\..\music\末班车-萧煌奇.mp3"); ;    //加载默认歌曲

            picB_Sound.Image = Image.FromFile(@"2.jpg");
            labLyric.BackColor = Color.Transparent;
            //labLyric.Parent = picB_Sound;//将pictureBox1设为标签的父控件
            ////pictureBox1.Controls.Add(label1);
            //labLyric.Location = new Point(80, 80);//重新设定标签的位置，这个位置时相对于父控件的左上角

        }

        int listSkinTally = 0;
        /// <summary>
        /// 单击更换窗体皮肤
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnChangeSkin_Click(object sender, EventArgs e)
        {
            listSkinTally++;
            //当增加至最大的一个索引时,判断
            if (listSkinTally == listSkin.Count) listSkinTally = 0;
            //更换窗体皮肤
            skinEngine1.SkinFile = listSkin[listSkinTally];
        }

        Random random = new Random();
        /// <summary>
        /// 每一秒更换一张图片
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void timer1_Tick(object sender, EventArgs e)
        {
            pictureBox1.Image = Image.FromFile(listPicture[random.Next(0, listPicture.Count)]);
        }

        /// <summary>
        /// 播放或暂停
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnPlayOrPause_Click(object sender, EventArgs e)
        {
            if (btnPlayOrPause.Text == "播放")
            {
                if (listBox_Song.SelectedIndex == -1)
                {
                    return;     //未添加相关歌曲,结束本方法
                }
                if (musicPlayer.URL == "")
                {
                    musicPlayer.URL = listSong[listBox_Song.SelectedIndex];
                }
                musicPlayer.Ctlcontrols.play(); //播放
                btnPlayOrPause.Text = "暂停";     //更改文本

                //加载歌词
                IsLrc(musicPlayer.URL);

            }
            else if (btnPlayOrPause.Text == "暂停")
            {
                musicPlayer.Ctlcontrols.pause();    //暂停
                btnPlayOrPause.Text = "播放";
            }
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            musicPlayer.Ctlcontrols.stop(); //停止
        }

        /// <summary>
        /// 选择音乐文件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnOpt_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Title = "请选择音乐文件";  //对话框标题
            ofd.Multiselect = true; //允许对话框多选
            ofd.InitialDirectory = @"‪C:\Users\MO\Music";   //初始目录
            ofd.Filter = @"音频文件|*.mp3;*.wma|All(*.*)|*.*"; //筛选文件
                                                           //展示对话框

            if (ofd.ShowDialog() == DialogResult.Cancel)
            {
                return;
            }
            //存储文件路径
            listSong.AddRange(ofd.FileNames);   //存储至Song集合中
            //遍历集合,存储值listBox控件列表中显示
            foreach (var item in listSong)
            {
                listBox_Song.Items.Add(Path.GetFileName(item));
            }

        }

        /// <summary>
        /// 双击播放音乐
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listBox1_DoubleClick(object sender, EventArgs e)
        {
            if (listBox_Song.SelectedIndex == -1)
            {
                return;     //未添加相关歌曲,结束本方法
            }
            musicPlayer.URL = listSong[listBox_Song.SelectedIndex];
            musicPlayer.Ctlcontrols.play(); //播放
            btnPlayOrPause.Text = "暂停";     //更改文本

            IsLrc(musicPlayer.URL);  //加载歌词
        }

        /// <summary>
        /// 上一曲
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUp_Click(object sender, EventArgs e)
        {
            if (listBox_Song.SelectedIndex == -1)
            {
                return;     //未添加相关歌曲,结束本方法
            }
            int temp = listBox_Song.SelectedIndex;  //获得当前索引
            //listBox判断索引,并修改
            if (listBox_Song.SelectedIndex == 0)
            {
                temp = listBox_Song.Items.Count - 1;
            }
            else
            {
                temp -= 1;
            }
            listBox_Song.SelectedIndices.Clear();//清空多选的索引
            listBox_Song.SelectedIndex = temp; //返回索引
            //音乐播放
            musicPlayer.URL = listSong[listBox_Song.SelectedIndex]; //更改播放路径
            musicPlayer.Ctlcontrols.play(); //播放
            btnPlayOrPause.Text = "暂停";
        }

        /// <summary>
        /// 下一曲
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDn_Click(object sender, EventArgs e)
        {
            PlayDown(); //下一曲方法
            musicPlayer.Ctlcontrols.play(); //播放
        }

        /// <summary>
        /// 播放下一曲
        /// </summary>
        private void PlayDown()
        {
            if (listBox_Song.SelectedIndex == -1)
            {
                return;     //未添加相关歌曲,结束本方法
            }
            int temp = listBox_Song.SelectedIndex;  //获得当前索引
            //listBox判断索引,并修改
            if (listBox_Song.SelectedIndex == listBox_Song.Items.Count - 1)
            {
                temp = 0;
            }
            else
            {
                temp += 1;
            }
            listBox_Song.SelectedIndices.Clear();//清空多选的索引
            listBox_Song.SelectedIndex = temp; //返回索引
            //音乐播放
            musicPlayer.URL = listSong[listBox_Song.SelectedIndex]; //更改播放路径
            btnPlayOrPause.Text = "暂停";
        }

        /// <summary>
        /// 多选删除歌曲
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void 删除ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int dnCount = listBox_Song.SelectedItems.Count;
            if (listBox_Song.SelectedIndex == -1)
            {
                return;
            }
                listSong.RemoveRange(listBox_Song.SelectedIndex, dnCount);
            for (int i = 0; i < dnCount; i++)
            {
                listBox_Song.Items.RemoveAt(listBox_Song.SelectedIndex);
            }

        }


        /// <summary>
        /// 播放器状态发生改变时
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void musicPlayer_PlayStateChange(object sender, AxWMPLib._WMPOCXEvents_PlayStateChangeEvent e)
        {
            //Read Playing Pause Ended Stop
            //播放结束时
            if (musicPlayer.playState == WMPLib.WMPPlayState.wmppsMediaEnded)
            {
                PlayDown();
            }

            //准备状态时
            if (musicPlayer.playState == WMPLib.WMPPlayState.wmppsReady)
            {
                try
                {
                    musicPlayer.Ctlcontrols.play(); //播放
                }
                catch { }


            }
        }

        /// <summary>
        /// 声音单击事件,静音或放音
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void picB_Sound_Click(object sender, EventArgs e)
        {
            //若静音,那么放音
            if (musicPlayer.settings.mute == false)
            {
                musicPlayer.settings.mute = true;
                picB_Sound.Image = Image.FromFile(@"1.jpg");
            }
            else
            {
                musicPlayer.settings.mute = false;
                picB_Sound.Image = Image.FromFile(@"2.jpg");
            }
        }

        /// <summary>
        /// 增加声音
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnUpSound_Click(object sender, EventArgs e)
        {
            musicPlayer.settings.volume += 5;
        }
        /// <summary>
        /// 减少声音
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnDnSound_Click(object sender, EventArgs e)
        {
            musicPlayer.settings.volume -= 5;
        }

        //存储歌词时间和歌词文本
        List<double> listLrcTime = new List<double>();
        List<string> listLrcTxt = new List<string>();
        bool bLrc = false;
        void IsLrc(string songPath)
        {
            //对应歌词的路径

            string lrc = Path.GetDirectoryName(songPath) + "\\" + Path.GetFileNameWithoutExtension(songPath) + ".lrc";
            if (File.Exists(lrc))//存在
            {
                //读取歌词
                string[] lrcArry = File.ReadAllLines(lrc, Encoding.Default);
                bLrc = true;    //有歌词标记位
                //加载歌词前,清空
                listLrcTime.Clear();
                listLrcTxt.Clear();
                for (int i = 0; i < lrcArry.Length; i++)
                {
                    if (lrcArry[i] == "") continue;//空值跳过
                    //[00:00.90]背过手 - 薛之谦
                    string[] temp = lrcArry[i].Split(new char[] { '[', ']' }, StringSplitOptions.RemoveEmptyEntries);
                    if (temp.Length == 1)//无歌词
                    {
                        continue;
                    }
                    // temp[0]:00:00.90  temp[1]:背过手 - 薛之谦
                    string[] temp1 = temp[0].Split(new char[] { ':' }, StringSplitOptions.RemoveEmptyEntries);
                    //temp1[0]:00   temp1[1]:00.90
                    double dTime = double.Parse(temp1[0]) * 60 + double.Parse(temp1[1]);
                    listLrcTime.Add(dTime);
                    listLrcTxt.Add(temp[1]);

                }

            }
            else
            {
                labLyric.Text = "---------------歌词未找到---------------";
                bLrc = false;
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {

            double time = 0d;
            time = musicPlayer.Ctlcontrols.currentPosition;  //播放时间
            if (musicPlayer.playState == WMPLib.WMPPlayState.wmppsPlaying)
            {
                label1.Text = musicPlayer.currentMedia.duration.ToString("#.00");//歌曲总时长
                time = musicPlayer.Ctlcontrols.currentPosition;  //播放时间
                label2.Text = time.ToString("#.00");
            }

            if (bLrc)
            {
                labLyric.Text = ShowLrc(time);
            }

        }

        /// <summary>
        /// 根据时间,输出歌词
        /// </summary>
        /// <param name="playTime"></param>
        /// <returns></returns>
        string ShowLrc(double playTime)
        {
            string lrc = listLrcTxt[0];
            if (playTime < listLrcTime[1])
            {
                return lrc;
            }
            for (int i = 0; i < listLrcTime.Count; i++)
            {
                if (i < listLrcTime.Count - 1)
                {
                        if (playTime >= listLrcTime[i] && playTime < listLrcTime[i + 1])
                    {
                            lrc = listLrcTxt[i];
                        break;
                    }
                 
                }
                else if (i == listLrcTime.Count - 1)
                {
                    lrc = listLrcTxt[listLrcTime.Count - 1];
                    break;
                }
            }
            return lrc;

        }
    }
}
