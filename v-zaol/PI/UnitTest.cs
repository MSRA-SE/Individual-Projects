using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PI
{
    public class UnitTest
    {
        public static void TestPI()
        {
            string[] s = {"50","14159265358979323846264338327950288419716939937510",
                          "100","58209749445923078164062862089986280348253421170679",
                         "10000","46101264836999892256959688159205600101655256375678",
                        "12000","66830082383404656475880405138080163363887421637140",
                        "15000","11732131389574706208847480236537103115089842799275",
                        "20000","29681062037765788371669091094180744878140490755178",
                        "50000","06526234053394391421112718106910522900246574236041",
                        "75000","17161339575779076637076456957025973880043841580589"};
            for (int i = 0; i < s.Length; i = i + 2)
            {
                int n = Convert.ToInt32(s[i]);
                compute.N = n;
                Program.pre();
                Program.computePI();
                string ans = Program.print(Program.ans);
                ans = ans.Substring(n - 50, 50);
                    
                if (ans != s[i + 1])
                {
                    Console.WriteLine("[ERROR PI wrong when N = " + n + "]");
                    Console.WriteLine(ans.Length);
                    Console.WriteLine(ans);
                    Console.WriteLine(s[i + 1]);
                }
                Console.WriteLine("[N:" + n + " Finished]");
            }
            Console.WriteLine("[Test Finished]");
        }
    }
}
