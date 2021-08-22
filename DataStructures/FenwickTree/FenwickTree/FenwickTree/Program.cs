using System;

namespace FenwickTreeApp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello Fenwick Tree!");

            int[] heightRisk = new int[] { 0, 10, 28, 3, 2, 7, 4, 6, -53 };

            FenwickTree fenwickTree = new FenwickTree(9);

            for (int i = 1; i < 9; i++)
            {
                fenwickTree.IncrementAtIndex(i, heightRisk[i]);
            }

            Console.WriteLine(fenwickTree.RangeSumQuery(1, 1));
            Console.WriteLine(fenwickTree.RangeSumQuery(1, 2));
            Console.WriteLine(fenwickTree.RangeSumQuery(1, 3));
            Console.WriteLine(fenwickTree.RangeSumQuery(3, 8));
            Console.WriteLine(fenwickTree.RangeSumQuery(1, 8));

            fenwickTree.IncrementAtIndex(3, 10);
            Console.WriteLine(fenwickTree.RangeSumQuery(1, 8));

            fenwickTree.IncrementAtIndex(3, -10);
            Console.WriteLine(fenwickTree.RangeSumQuery(1, 8));

            Console.ReadKey();
        }
    }

    public class FenwickTree
    {
        private const int Zero = 0;

        private readonly int[] cumulativeTable;

        public FenwickTree(int size)
        {
            cumulativeTable = new int[size];          
        }

        public int LeastSignificantOneBitOf(int number)
        {
            return (number & (-number));
        }

        public int RangeSumQuery(int endIndex)
        {
            int sum = 0;
            for (; endIndex > 0; endIndex -= LeastSignificantOneBitOf(endIndex))
            {
                sum += cumulativeTable[endIndex];
            }
            return sum;
        }

        public int RangeSumQuery(int startIndex, int endIndex)
        {
            int rangeToSubtract = startIndex == 1 ? Zero : RangeSumQuery(startIndex - 1);
            return RangeSumQuery(endIndex) - rangeToSubtract;
        }

        public void IncrementAtIndex(int index, int value)
        {
            for (; index < cumulativeTable.Length; index += LeastSignificantOneBitOf(index))
            {
                cumulativeTable[index] += value;
            }
        }
    }
}
