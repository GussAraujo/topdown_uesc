function main(nums, val) {
  let newNums = []
  for (let i = 0, j = 0; i < nums.length; i++) {
    if (nums[i] != val) {
      newNums[j++] = nums[i]
    }
  }

  return newNums.length
}

console.log(main([3,2,2,3], 3))