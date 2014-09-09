using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ComputePI;

namespace UnitTest
{
    /// <summary>
    /// (Xia)没来得及写完，接下来仿照testMax(测试已经通过)写完全部单元测试
    /// </summary>
    [TestClass]
    public class computeTest
    {
        [TestMethod]
        public void testMax()
        {
            long a = 20000000;
            long b = 1000000;
            long expected = a;
            long actual;
            actual=compute.max(a, b);
            Assert.AreEqual(expected,actual);
            Assert.Inconclusive("验证max的正确性");
        }
    }
}
