function main(x) {
  if (x < 0) return false

  let aux = x
  let invertido = 0
  
  while (aux != 0) {
    invertido = invertido * 10 + (aux % 10)
    aux = ~~(aux / 10)
  }

  return invertido == x
}

console.log(main(12321))