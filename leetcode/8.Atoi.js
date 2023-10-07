function main(s) {
  let res = 0
  let index = []

  if (s[0] != '-' && s[0] != ' ' && Number.isNaN(Number(s[0]))) {
    return 0
  }

  for (let i = 0; i < s.length; i++) {
    if (s[i] == '.') break
    if(!Number.isNaN(Number(s[i])) && Number(s[i]) != ' ') {
      index.push(i)
      res = res * 10 + Number(s[i])
    }
  }

  res = s[index[0]-1] == '-' ? -res : res

  if (res < -Math.pow(2,31)) return -Math.pow(2,31)
  else if(res > Math.pow(2,31) - 1) return Math.pow(2,31) - 1
  else return res

}

console.log(main("-+12"))