using FenwickTreeApp;
using Xunit;

namespace UnitTests
{
    public class RangeSumQuery
    {
        [Theory]
        [InlineData(1, 1, 10)]
        [InlineData(2, 2, 28)]
        [InlineData(3, 3, 3)]
        [InlineData(4, 4, 2)]
        [InlineData(5, 5, 7)]
        [InlineData(6, 6, 4)]
        [InlineData(7, 7, 6)]
        [InlineData(8, 8, -53)]
        public void ShouldCalculateRangeSumQueryWhenIsSingleIndex(int heightStart, int heightEnd, int rangeRisk)
        {
            //Arrange
            int[] heightRisk = new int[] { 0, 10, 28, 3, 2, 7, 4, 6, -53 };

            FenwickTree fenwickTree = new FenwickTree(9);

            for (int i = 1; i < 9; i++)
            {
                fenwickTree.IncrementAtIndex(i, heightRisk[i]);
            }

            //Act
            int result = fenwickTree.RangeSumQuery(heightStart, heightEnd);

            //Assert
            Assert.Equal(result, rangeRisk);
        }

        [Theory]
        [InlineData(1, 2, 38)]
        [InlineData(1, 3, 41)]
        [InlineData(6, 8, -43)]
        [InlineData(3, 7, 22)]
        [InlineData(1, 8, 7)]
        public void ShouldCalculateRangeSumQuery(int heightStart, int heightEnd, int rangeRisk)
        {
            //Arrange
            int[] heightRisk = new int[] { 0, 10, 28, 3, 2, 7, 4, 6, -53 };

            FenwickTree fenwickTree = new FenwickTree(9);

            for (int i = 1; i < 9; i++)
            {
                fenwickTree.IncrementAtIndex(i, heightRisk[i]);
            }

            //Act
            int result = fenwickTree.RangeSumQuery(heightStart, heightEnd);

            //Assert
            Assert.Equal(result, rangeRisk);
        }

        [Theory]
        [InlineData(1, 8, -3)]
        [InlineData(1, 1, 0)]
        public void ShouldCalculateRangeSumQueryWithNegativeIncrement(int heightStart, int heightEnd, int rangeRisk)
        {
            //Arrange
            int[] heightRisk = new int[] { 0, 10, 28, 3, 2, 7, 4, 6, -53 };

            FenwickTree fenwickTree = new FenwickTree(9);

            for (int i = 1; i < 9; i++)
            {
                fenwickTree.IncrementAtIndex(i, heightRisk[i]);
            }

            //Act
            fenwickTree.IncrementAtIndex(1, -10);
            int result = fenwickTree.RangeSumQuery(heightStart, heightEnd);

            //Assert
            Assert.Equal(result, rangeRisk);
        }
    }
}
