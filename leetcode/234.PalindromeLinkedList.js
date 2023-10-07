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

function main(head) {
  let arr = []
  let list = head

  while (list != null) {
    arr.push(list.val)
    list = list.next
  }

  return arr.join('') == arr.reverse().join('')
}

console.log(main(createList([1,2,3,2,1])))