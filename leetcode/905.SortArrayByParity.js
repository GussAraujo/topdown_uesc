function main(nums) {
  let i = 0
  let j = nums.length-1

  while (i != j) {
    if (!(nums[i] % 2)) i++
    else if ((nums[j] % 2)) j--
    else [nums[i], nums[j]] = [nums[j], nums[i]]
  }
  
  return nums
}

console.log(main([3,1,2,4]))