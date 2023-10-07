function main(string) {
  let newString = []
  
  for (let str of string.split(' ')) {
    newString.push(str.split('').reverse().join(''))
  }

  return newString.join(' ')
}

console.log(main("Let's take LeetCode contest"))