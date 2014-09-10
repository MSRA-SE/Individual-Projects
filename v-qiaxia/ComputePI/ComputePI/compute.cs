using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ComputePI
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
                long t = a[i] + next;
                a[i] = t % carry;
                next = t / carry;
            }
            return a;
        }
    }
}
