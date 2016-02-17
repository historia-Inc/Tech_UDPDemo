using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UDPStub
{
    class NetworkProtocolColor : INetworkProtocol
    {
        public float R, G, B;

        public void Serialize(out byte[] serializedData)
        {
            List<byte> cache = new List<byte>();

            // 0~1の範囲にに変換
            cache.AddRange(BitConverter.GetBytes(R / 255f));
            cache.AddRange(BitConverter.GetBytes(G / 255f));
            cache.AddRange(BitConverter.GetBytes(B / 255f));
            cache.AddRange(BitConverter.GetBytes(1.0f));

            // タイムスタンプ
            TimeSpan TotalTimeSpan = DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
            float TimeStamp = (float)TotalTimeSpan.TotalMilliseconds;
            cache.AddRange(BitConverter.GetBytes(TimeStamp));

            serializedData = cache.ToArray();
            return;
        }
    }
}
