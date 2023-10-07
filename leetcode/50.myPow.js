function main(x, n) {
  if (x == 1) return 1

  if (n < 0) {
    n = -n
    x = 1/x
  }

  let aux = 1
  
  for (let i = 0; i < n; i++) {
    aux *= x
  }

  return [aux, Math.pow(x, n)]
}

console.log(main(2, -2))