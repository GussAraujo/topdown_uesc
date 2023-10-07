function main(n) {
  let fib = [1, 2, 3]

  for (let i = 3; i <= n; i++) {
    fib[i] = fib[i-1] + fib[i-2]
  }

  return fib[n-1]
}

console.log(main(5))