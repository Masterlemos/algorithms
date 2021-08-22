using FenwickTreeApp;
using System;
using Xunit;

namespace UnitTests
{
    public class LeastSignificantBit
    {
        [Theory]
        [InlineData(4, 4)]
        [InlineData(1, 1)]
        [InlineData(2, 2)]
        [InlineData(3, 1)]
        [InlineData(5, 1)]
        [InlineData(6, 2)]
        [InlineData(8, 8)]
        [InlineData(9, 1)]
        [InlineData(10, 2)]

        public void ShouldCalculateLeastSignificantOneBit(int number, int leastSignificantOneBit)
        {
            //Arrange
            FenwickTree fenwickTree = new FenwickTree(11);

            //Act
            int result = fenwickTree.LeastSignificantOneBitOf(number);

            //Assert
            Assert.Equal(result, leastSignificantOneBit);
        }
    }
}
