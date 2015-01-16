using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ComputePI
{
    
    public class Program
    {
        public static long[] ans;
        static long[] a;
        static long[] b;
        static long[] x5;
        static long[] x239;
        static long n, m;
        static bool flag5, flag239;

        static void arctg5()
        {
            if (n % 2 == 1)
            {
                a = compute.add(a, compute.div(x5, 2 * n - 1));
            }
            else
            {
                a = compute.minus(a, compute.div(x5, 2 * n - 1));
            }
            x5 = compute.div(x5, 25);
        }
        static void arctg239()
        {
            if (m % 2 == 1)
            {
                b = compute.add(b, compute.div(x239, 2 * m - 1));
            }
            else
            {
                b = compute.minus(b, compute.div(x239, 2 * m - 1));
            }
            x239 = compute.div(x239, 57121);
        }
        static void thread5()
        {
            long[] a5;
            n = 1;
            flag5 = false;
            while (true)
            {
                a5 = a;
                arctg5();
                if (notChange(a5, a))
                    break;
                n = n + 1;
            }
            a = compute.mul(a, 4);
            flag5 = true;
        }
        static void thread239()
        {
            long[] b239;
            m = 1;
            flag239 = false;
            while (true)
            {
                b239 = b;
                arctg239();
                if (notChange(b239, b))
                    break;
                m = m + 1;
            }
            b = compute.mul(b, 2);
            flag239 = true;
        }

        public static void computePI()
        {
            Thread t5 = new Thread(thread5);
            Thread t239 = new Thread(thread239);
            t5.Start();
            t239.Start();
            while (!(flag5 && flag239))
            {
            }
            ans = compute.minus(a, b);
        }

        static bool notChange(long[] check, long[] ans)
        {
            long time = compute.times();
            for (int i = 0; i < time; i++)
                if (check[i] != ans[i]) return false;
            return true;
        }

        public static string ansStr(long[] ans)
        {
            string[] zero = { "", "0", "00", "000", "0000", "00000", "000000", "0000000" };
            string answer = "";
            long time = compute.times();
            for (int i = (int)time - 2; i >= 0; i--)
            {
                string s = ans[i].ToString();
                s = zero[compute.digit - s.Length] + s;
                answer += s;
            }

            return answer;
        }

        public static void pre()
        {
            long time = compute.times();
            ans = new long[time];
            a = new long[time];
            b = new long[time];
            x5 = new long[time];
            x239 = new long[time];
            flag239 = false;
            flag5 = false;
            n = 1;
            m = 1;
            x5[time - 1] = 1;
            x5 = compute.div(x5, 5);

            x239[time - 1] = 1;
            x239 = compute.div(x239, 239);
        }

        static void Compute(string arg)
        {
            compute.N = Convert.ToInt64(arg);
            if (compute.N == 0)
            {
                return;
            }
            pre();
            computePI();
            string answer = ansStr(ans);
            for (int i = 0; i < compute.N; i++)
            {
                Console.Write(answer[i]);
                if ((i + 1) % 10 == 0)
                {
                    Console.WriteLine();
                }
            }
        }

        static void Main(string[] args)
        {
            System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();
            sw.Start();
            Compute(args[0]);
            sw.Stop();
            TimeSpan ts = sw.Elapsed;
            Console.WriteLine("\t\tTime(sec):" + ts.TotalSeconds);
        }
    }
}
