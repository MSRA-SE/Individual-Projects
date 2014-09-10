using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
namespace PI
{
    public class compute
    {
        public static long N = 20;
        public static long digit = 7;
        public static long carry = 10000000;
        public static long times()
        {
            return N / digit + 5;
        }
        public static long max(long a, long b)
        {
            return a > b ? a : b;
        }
        public static long[] add(long[] a, long[] b)
        {
            long time = times();
            long[] c = new long[time];
            c[0] = a[0] + b[0];
            long next = c[0] / carry;
            c[0] = c[0] % carry;
            for (int i = 1; i < time; i++)
            {
                c[i] = a[i] + b[i] + next;
                next = c[i] / carry;
                c[i] = c[i] % carry;
            }
            return c;
        }

        public static long[] minus(long[] a, long[] b)
        {
            long time = times();
            long[] c = new long[time];
            c[0] = (a[0] - b[0] + carry) % carry;
            long next = (a[0] - b[0] + carry) / carry - 1;
            for (int i = 1; i < time; i++)
            {
                long t = a[i] - b[i] + next + carry;
                c[i] = t % carry;
                next = t / carry - 1;
            }
            return c;
        }

        public static long[] div(long[] a, long b)
        {
            long time = times();
            long[] c = new long[time];
            c[time - 1] = a[time - 1] / b;
            long next = a[time - 1] % b;
            for (int i = (int)time - 2; i >= 0; i--)
            {
                long t = a[i] + next * carry;
                c[i] = t / b;
                next = t % b;
            }
            return c;
        }

        public static long[] mul(long[] a, long b)
        {
            long time = times();
            for (int i = 0; i < time; i++)
                a[i] = a[i] << (int)b;
            long next = a[0] / carry;
            a[0] = a[0] % carry;
            for (int i = 1; i < time; i++)
            {
                long t = a[i]+next;
                a[i] = t % carry;
                next = t / carry;
            }
            return a;
        }


    }
    public class Program
    {
        public static long[] ans;
        static long[] a;
        static long[] b;
        static long[] x5;
        static long[] x239;
        static long n,m;
        static bool flag5, flag239;

        static void arctg5()
        {
            if (n % 2 == 1)
            {
                a = compute.add(a,compute.div(x5, 2 * n - 1));
            }
            else
            {
                a = compute.minus(a,compute.div(x5, 2 * n - 1));
            }
            x5 = compute.div(x5, 25); 
        }
        static void arctg239()
        {
            if (m % 2 == 1)
            {
                b = compute.add(b,compute.div(x239, 2 * m - 1));
            }
            else
            {
                b = compute.minus(b,compute.div(x239, 2 * m - 1));
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
            while (!(flag5 && flag239)) {
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

        public static string print(long[] ans)
        {
            string[] zero = { "","0", "00", "000", "0000", "00000", "000000", "0000000" };
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

        static void test()
        {
            UnitTest.TestPI();
        }

        static void doit(string arg)
        {
            compute.N = Convert.ToInt64(arg);
            //System.Diagnostics.Stopwatch sw = new System.Diagnostics.Stopwatch();
            //sw.Start();
            if (compute.N == 0)
            {
                return;
            }
            pre();
            computePI();
            //sw.Stop();
            //TimeSpan ts = sw.Elapsed;
            string answer = print(ans);
            for (int i = 0; i < compute.N; i++)
            {
                Console.Write(answer[i]);
                if ((i + 1) % 10 == 0)
                {
                    Console.WriteLine();
                }
            }
            //Console.WriteLine("N:" + n + " M:" + m);
            //Console.WriteLine("Time:" + ts.TotalSeconds);
            //Console.WriteLine("Time:" + ts.TotalMilliseconds);
        }

        static void Main(string[] args)
        {
            //test();
            doit(args[0]);
        }
    }
}
