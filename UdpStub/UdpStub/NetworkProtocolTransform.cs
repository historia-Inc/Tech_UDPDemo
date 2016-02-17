using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace UDPStub
{
    public class NetworkProtocolTransform : INetworkProtocol
    {
        public struct Location
        {
            public float X, Y, Z;
        }

        public struct Rotator
        {
            public float Pitch, Yaw, Roll;
        }

        public struct Scale
        {
            public float X, Y, Z;
        }

        public Location location;
        public Rotator rotator;
        public Scale scale;

        public void Serialize(out byte[] serializedData)
        {
            // シリアライズ
            List<byte> cache = new List<byte>();

            cache.AddRange(BitConverter.GetBytes(location.X));
            cache.AddRange(BitConverter.GetBytes(location.Y));
            cache.AddRange(BitConverter.GetBytes(location.Z));
            cache.AddRange(BitConverter.GetBytes(rotator.Pitch));
            cache.AddRange(BitConverter.GetBytes(rotator.Yaw));
            cache.AddRange(BitConverter.GetBytes(rotator.Roll));
            cache.AddRange(BitConverter.GetBytes(scale.X));
            cache.AddRange(BitConverter.GetBytes(scale.Y));
            cache.AddRange(BitConverter.GetBytes(scale.Z));

            // タイムスタンプ
            TimeSpan TotalTimeSpan = DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, DateTimeKind.Utc);
            float TimeStamp = (float)TotalTimeSpan.TotalMilliseconds;
            cache.AddRange(BitConverter.GetBytes(TimeStamp));

            serializedData = cache.ToArray();
            return;
        }
    }
}
