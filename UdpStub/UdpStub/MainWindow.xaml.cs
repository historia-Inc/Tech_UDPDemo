using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Media;
using System.Net.Sockets;

namespace UDPStub
{
    /// <summary>
    /// MainWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class MainWindow : Window
    {
        Color boxColor;
        NetworkProtocolTransform currentTransform = new NetworkProtocolTransform();
        NetworkProtocolColor currentColor = new NetworkProtocolColor();

        //UDP通信で使うプロパティ
        UdpClient udpSocket;
        string localHostIp = "127.0.0.1";
        /// <summary>
        /// 各プロトコルで使用するポート番号
        /// </summary>
        enum UsePort : int
        {
            Transform = 50001,
            Color = 50002,
        }

        public MainWindow()
        {
            InitializeComponent();
            udpSocket = new UdpClient();

            //値が変わった時にデータを送信するイベントを追加
            X.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            Y.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            Z.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            Roll.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            Pitch.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            Yaw.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            ScaleX.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            ScaleY.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);
            ScaleZ.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendTransform);

            R.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendColor);
            G.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendColor);
            B.ValueChanged += new RoutedPropertyChangedEventHandler<double>(SendColor);
        }

        /// <summary>
        /// 矩形UIに表示している色を更新
        /// </summary>
        void UpdateBoxColor()
        {
            boxColor.R = (byte)R.Value;
            boxColor.G = (byte)G.Value;
            boxColor.B = (byte)B.Value;
            boxColor.A = 255;
            ColorBox.Fill = new SolidColorBrush(boxColor);
        }

        #region Events
        /*
        **　各値変更時に呼ばれるイベント　UIと内部数値の更新を行う
        */
        private void X_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.location.X = (float)X.Value;
            value_X.Text = X.Value.ToString();
        }

        private void Y_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.location.Y = (float)Y.Value;
            value_Y.Text = Y.Value.ToString();
        }

        private void Z_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.location.Z = (float)Z.Value;
            value_Z.Text = Z.Value.ToString();
        }

        private void Roll_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.rotator.Roll = (float)Roll.Value;
            value_Roll.Text = Roll.Value.ToString();
        }

        private void Pitch_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.rotator.Pitch = (float)Pitch.Value;
            value_Pitch.Text = Pitch.Value.ToString();
        }

        private void Yaw_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.rotator.Yaw = (float)Yaw.Value;
            value_Yaw.Text = Yaw.Value.ToString();
        }

        private void ScaleX_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.scale.X = (float)ScaleX.Value;
            value_ScaleX.Text = ScaleX.Value.ToString();
        }

        private void ScaleY_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.scale.Y = (float)ScaleY.Value;
            value_ScaleY.Text = ScaleY.Value.ToString();
        }

        private void ScaleZ_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentTransform.scale.Z = (float)ScaleZ.Value;
            value_ScaleZ.Text = ScaleZ.Value.ToString();
        }

        private void R_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentColor.R = (float)R.Value;
            value_R.Text = R.Value.ToString();
            UpdateBoxColor();
        }

        private void G_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentColor.G = (float)G.Value;
            value_G.Text = G.Value.ToString();
            UpdateBoxColor();
        }

        private void B_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            currentColor.B = (float)B.Value;
            value_B.Text = B.Value.ToString();
            UpdateBoxColor();
        }

        /*
        **　UDPでデータを送信
        */
        private void SendTransform(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            byte[] sendBuf;

            currentTransform.Serialize(out sendBuf);

            //送信
            udpSocket.Send(sendBuf, sendBuf.Length, localHostIp, (int)UsePort.Transform);
        }

        private void SendColor(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            byte[] sendBuf;

            currentColor.Serialize(out sendBuf);

            //送信
            udpSocket.Send(sendBuf, sendBuf.Length, localHostIp, (int)UsePort.Color);
        }
        #endregion
    }
}