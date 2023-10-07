function ListNode(val, next) {
  this.val = (val === undefined ? 0 : val)
  this.next = (next === undefined ? null : next)
}

function createList(l1) {
  let list = new ListNode(l1[0])
  let selectedNode = list

  for (let i = 1; i < l1.length; i++) {
    selectedNode.next = new ListNode(l1[i])
    selectedNode = selectedNode.next
  }

  return list
}

function main(l1, l2) {
  let l1Array = []
  let l1Head = l1
  
  while (l1Head != null) {
    l1Array.push(l1Head.val)
    l1Head = l1Head.next
  }

  let l2Array = []
  let l2Head = l2

  while (l2Head != null) {
    l2Array.push(l2Head.val)
    l2Head = l2Head.next
  }

  let sum = BigInt(0)
  for (let i = l1Array.length-1; i >= 0; i--) {
    sum = sum * BigInt(10) + BigInt(l1Array[i])
  }

  let sum2 = BigInt(0)
  for (let i = l2Array.length-1; i >= 0; i--) {
    sum2 = sum2 * BigInt(10) + BigInt(l2Array[i])
  }

  const sumAll = sum + sum2
  const result =  Array.from(String(sumAll), Number);
  
  result.reverse()

  let i = 0
  let list = new ListNode(result[i])
  let selectedNode = list

  for (; i < result.length - 1; ++i) {
    selectedNode.next = new ListNode(result[i+1])
    selectedNode = selectedNode.next
  }

  return list
}

console.log(main(createList([1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1]), createList([5,6,4])))

