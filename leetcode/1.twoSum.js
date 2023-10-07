/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
function main(nums, target) {
  let i = 0
  let j = nums.length

  let oldArray = [...nums]
  nums.sort((a, b) => a - b)

  while (i != j){ 
    if (nums[i] + nums[j-1]  > target)
      j--
    else if (nums[i] + nums[j-1] < target)
      i++
    else {
      i = oldArray.findIndex(n => n == nums[i])
      oldArray[i] = -1
      j = oldArray.findIndex(n => n == nums[j-1])
      return [i, j]
    }
  }
};

console.log(main([3,3], 6))