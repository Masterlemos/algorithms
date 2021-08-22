using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace SpojFrequentValues
{
    public class Test
    {
        private static TextReader reader;
        private static TextWriter writer;

        private static Queue<string> currentLineTokens = new Queue<string>();

        private static string[] ReadSplittedLine() { 
            return reader.ReadLine().Split(new[] { ' ', '\t', }, StringSplitOptions.RemoveEmptyEntries); 
        }

        public static string ReadToken() {
            while (currentLineTokens.Count == 0)
            {
                currentLineTokens = new Queue<string>(ReadSplittedLine());
            }
            return currentLineTokens.Dequeue(); 
        }

        public static long ReadLong() { 
            return long.Parse(ReadToken()); 
        }

        public static long ReadSingleLong() { 
            return long.Parse(reader.ReadLine()); 
        }

        public static long[] ReadLongArray() { 
            return ReadSplittedLine().Select(long.Parse).ToArray(); 
        }

        public static void WriteLines(IEnumerable<long> answers) {
            foreach (var a in answers)
            {
                writer.WriteLine(a);
            }
        }

        public static void Main()
        {
            reader = new StreamReader(Console.OpenStandardInput());
            writer = new StreamWriter(Console.OpenStandardOutput());

            long numberOfValues = ReadSingleLong();
            FenwickTree fenwickTree = new FenwickTree(numberOfValues + 1);
            
            long[] values = ReadLongArray();
            for (int i = 0; i < numberOfValues; i++)
            {
                long value = values[i];
                fenwickTree.IncrementAtIndex(i+1, value);
            }

            long numberOfOperations = ReadSingleLong();
            var answers = new List<long>();

            for (int i = 0; i < numberOfOperations; i++)
            {
                var operation = ReadToken();
                if (operation == "q")
                {
                    answers.Add(fenwickTree.RangeSumQuery(ReadLong(), ReadLong()));
                }
                else
                {
                    fenwickTree.IncrementAtIndex(ReadLong(), ReadLong());
                }
            }
            WriteLines(answers);
            reader.Close();
            writer.Close();
        }
    }

    public class FenwickTree
    {
        private const int Zero = 0;

        private readonly long[] cumulativeTable;

        public FenwickTree(long size)
        {
            cumulativeTable = new long[size];
        }

        public long LeastSignificantOneBitOf(long number)
        {
            return (number & (-number));
        }

        public long RangeSumQuery(long endIndex)
        {
            long sum = 0;
            for (; endIndex > 0; endIndex -= LeastSignificantOneBitOf(endIndex))
            {
                sum += cumulativeTable[endIndex];
            }
            return sum;
        }

        public long RangeSumQuery(long startIndex, long endIndex)
        {
            long rangeToSubtract = startIndex == 1 ? Zero : RangeSumQuery(startIndex - 1);
            return RangeSumQuery(endIndex) - rangeToSubtract;
        }

        public void IncrementAtIndex(long index, long value)
        {
            for (; index < cumulativeTable.Length; index += LeastSignificantOneBitOf(index))
            {
                cumulativeTable[index] += value;
            }
        }
    }
}
