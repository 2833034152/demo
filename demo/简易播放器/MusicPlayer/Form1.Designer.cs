
namespace MusicPlayer
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
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.skinEngine1 = new Sunisoft.IrisSkin.SkinEngine(((System.ComponentModel.Component)(this)));
            this.btnChangeSkin = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btnPlayOrPause = new System.Windows.Forms.Button();
            this.btnStop = new System.Windows.Forms.Button();
            this.btnOpt = new System.Windows.Forms.Button();
            this.listBox_Song = new System.Windows.Forms.ListBox();
            this.btnUp = new System.Windows.Forms.Button();
            this.btnDn = new System.Windows.Forms.Button();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.删除ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.picB_Sound = new System.Windows.Forms.PictureBox();
            this.btnUpSound = new System.Windows.Forms.Button();
            this.btnDnSound = new System.Windows.Forms.Button();
            this.labLyric = new System.Windows.Forms.Label();
            this.musicPlayer = new AxWMPLib.AxWindowsMediaPlayer();
            this.timerLrc = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.contextMenuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picB_Sound)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.musicPlayer)).BeginInit();
            this.SuspendLayout();
            // 
            // skinEngine1
            // 
            this.skinEngine1.SerialNumber = "";
            this.skinEngine1.SkinFile = null;
            // 
            // btnChangeSkin
            // 
            this.btnChangeSkin.Location = new System.Drawing.Point(409, 11);
            this.btnChangeSkin.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.btnChangeSkin.Name = "btnChangeSkin";
            this.btnChangeSkin.Size = new System.Drawing.Size(76, 38);
            this.btnChangeSkin.TabIndex = 0;
            this.btnChangeSkin.Text = "换肤";
            this.btnChangeSkin.UseVisualStyleBackColor = true;
            this.btnChangeSkin.Click += new System.EventHandler(this.btnChangeSkin_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.pictureBox1.Location = new System.Drawing.Point(1, 2);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(404, 408);
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btnPlayOrPause
            // 
            this.btnPlayOrPause.Location = new System.Drawing.Point(409, 73);
            this.btnPlayOrPause.Margin = new System.Windows.Forms.Padding(2);
            this.btnPlayOrPause.Name = "btnPlayOrPause";
            this.btnPlayOrPause.Size = new System.Drawing.Size(76, 38);
            this.btnPlayOrPause.TabIndex = 3;
            this.btnPlayOrPause.Text = "播放";
            this.btnPlayOrPause.UseVisualStyleBackColor = true;
            this.btnPlayOrPause.Click += new System.EventHandler(this.btnPlayOrPause_Click);
            // 
            // btnStop
            // 
            this.btnStop.Location = new System.Drawing.Point(409, 133);
            this.btnStop.Margin = new System.Windows.Forms.Padding(2);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(76, 38);
            this.btnStop.TabIndex = 4;
            this.btnStop.Text = "停止";
            this.btnStop.UseVisualStyleBackColor = true;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // btnOpt
            // 
            this.btnOpt.Location = new System.Drawing.Point(409, 197);
            this.btnOpt.Margin = new System.Windows.Forms.Padding(2);
            this.btnOpt.Name = "btnOpt";
            this.btnOpt.Size = new System.Drawing.Size(76, 38);
            this.btnOpt.TabIndex = 5;
            this.btnOpt.Text = "添加";
            this.btnOpt.UseVisualStyleBackColor = true;
            this.btnOpt.Click += new System.EventHandler(this.btnOpt_Click);
            // 
            // listBox_Song
            // 
            this.listBox_Song.BackColor = System.Drawing.SystemColors.Menu;
            this.listBox_Song.ContextMenuStrip = this.contextMenuStrip1;
            this.listBox_Song.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.listBox_Song.FormattingEnabled = true;
            this.listBox_Song.ItemHeight = 16;
            this.listBox_Song.Location = new System.Drawing.Point(490, 12);
            this.listBox_Song.Name = "listBox_Song";
            this.listBox_Song.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
            this.listBox_Song.Size = new System.Drawing.Size(194, 436);
            this.listBox_Song.TabIndex = 6;
            this.listBox_Song.DoubleClick += new System.EventHandler(this.listBox1_DoubleClick);
            // 
            // btnUp
            // 
            this.btnUp.Location = new System.Drawing.Point(409, 252);
            this.btnUp.Margin = new System.Windows.Forms.Padding(2);
            this.btnUp.Name = "btnUp";
            this.btnUp.Size = new System.Drawing.Size(76, 38);
            this.btnUp.TabIndex = 7;
            this.btnUp.Text = "上一曲";
            this.btnUp.UseVisualStyleBackColor = true;
            this.btnUp.Click += new System.EventHandler(this.btnUp_Click);
            // 
            // btnDn
            // 
            this.btnDn.Location = new System.Drawing.Point(409, 307);
            this.btnDn.Margin = new System.Windows.Forms.Padding(2);
            this.btnDn.Name = "btnDn";
            this.btnDn.Size = new System.Drawing.Size(76, 38);
            this.btnDn.TabIndex = 8;
            this.btnDn.Text = "下一曲";
            this.btnDn.UseVisualStyleBackColor = true;
            this.btnDn.Click += new System.EventHandler(this.btnDn_Click);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.删除ToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(101, 26);
            // 
            // 删除ToolStripMenuItem
            // 
            this.删除ToolStripMenuItem.Name = "删除ToolStripMenuItem";
            this.删除ToolStripMenuItem.Size = new System.Drawing.Size(100, 22);
            this.删除ToolStripMenuItem.Text = "删除";
            this.删除ToolStripMenuItem.Click += new System.EventHandler(this.删除ToolStripMenuItem_Click);
            // 
            // picB_Sound
            // 
            this.picB_Sound.Location = new System.Drawing.Point(114, 416);
            this.picB_Sound.Name = "picB_Sound";
            this.picB_Sound.Size = new System.Drawing.Size(25, 25);
            this.picB_Sound.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.picB_Sound.TabIndex = 10;
            this.picB_Sound.TabStop = false;
            this.picB_Sound.Click += new System.EventHandler(this.picB_Sound_Click);
            // 
            // btnUpSound
            // 
            this.btnUpSound.Location = new System.Drawing.Point(251, 416);
            this.btnUpSound.Name = "btnUpSound";
            this.btnUpSound.Size = new System.Drawing.Size(30, 25);
            this.btnUpSound.TabIndex = 11;
            this.btnUpSound.Text = "➕";
            this.btnUpSound.UseVisualStyleBackColor = true;
            this.btnUpSound.Click += new System.EventHandler(this.btnUpSound_Click);
            // 
            // btnDnSound
            // 
            this.btnDnSound.Location = new System.Drawing.Point(215, 416);
            this.btnDnSound.Name = "btnDnSound";
            this.btnDnSound.Size = new System.Drawing.Size(30, 25);
            this.btnDnSound.TabIndex = 12;
            this.btnDnSound.Text = "➖";
            this.btnDnSound.UseVisualStyleBackColor = true;
            this.btnDnSound.Click += new System.EventHandler(this.btnDnSound_Click);
            // 
            // labLyric
            // 
            this.labLyric.AutoSize = true;
            this.labLyric.BackColor = System.Drawing.Color.Transparent;
            this.labLyric.Font = new System.Drawing.Font("宋体", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labLyric.Location = new System.Drawing.Point(6, 352);
            this.labLyric.MaximumSize = new System.Drawing.Size(400, 50);
            this.labLyric.Name = "labLyric";
            this.labLyric.Size = new System.Drawing.Size(53, 18);
            this.labLyric.TabIndex = 13;
            this.labLyric.Text = "Lyric";
            // 
            // musicPlayer
            // 
            this.musicPlayer.Enabled = true;
            this.musicPlayer.Location = new System.Drawing.Point(1, 2);
            this.musicPlayer.Margin = new System.Windows.Forms.Padding(2);
            this.musicPlayer.Name = "musicPlayer";
            this.musicPlayer.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("musicPlayer.OcxState")));
            this.musicPlayer.Size = new System.Drawing.Size(404, 447);
            this.musicPlayer.TabIndex = 1;
            this.musicPlayer.PlayStateChange += new AxWMPLib._WMPOCXEvents_PlayStateChangeEventHandler(this.musicPlayer_PlayStateChange);
            // 
            // timerLrc
            // 
            this.timerLrc.Enabled = true;
            this.timerLrc.Interval = 500;
            this.timerLrc.Tick += new System.EventHandler(this.timer2_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("宋体", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(419, 357);
            this.label1.MaximumSize = new System.Drawing.Size(400, 50);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 18);
            this.label1.TabIndex = 14;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("宋体", 13F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(419, 395);
            this.label2.MaximumSize = new System.Drawing.Size(400, 50);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 18);
            this.label2.TabIndex = 15;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684, 461);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.labLyric);
            this.Controls.Add(this.btnDnSound);
            this.Controls.Add(this.btnUpSound);
            this.Controls.Add(this.picB_Sound);
            this.Controls.Add(this.btnDn);
            this.Controls.Add(this.btnUp);
            this.Controls.Add(this.listBox_Song);
            this.Controls.Add(this.btnOpt);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.btnPlayOrPause);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.musicPlayer);
            this.Controls.Add(this.btnChangeSkin);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.MinimumSize = new System.Drawing.Size(700, 500);
            this.Name = "Form1";
            this.Text = "MusicPlayer";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.contextMenuStrip1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picB_Sound)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.musicPlayer)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Sunisoft.IrisSkin.SkinEngine skinEngine1;
        private System.Windows.Forms.Button btnChangeSkin;
        private AxWMPLib.AxWindowsMediaPlayer musicPlayer;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btnPlayOrPause;
        private System.Windows.Forms.Button btnStop;
        private System.Windows.Forms.Button btnOpt;
        private System.Windows.Forms.ListBox listBox_Song;
        private System.Windows.Forms.Button btnUp;
        private System.Windows.Forms.Button btnDn;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 删除ToolStripMenuItem;
        private System.Windows.Forms.PictureBox picB_Sound;
        private System.Windows.Forms.Button btnUpSound;
        private System.Windows.Forms.Button btnDnSound;
        private System.Windows.Forms.Label labLyric;
        private System.Windows.Forms.Timer timerLrc;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

