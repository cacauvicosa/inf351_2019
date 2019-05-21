/*! Author: Raphael Nepomuceno <raphael@nepomuceno.dev> */

const onReady = fn => {
  if (document.readyState !== 'loading') fn()
  else document.addEventListener('DOMContentLoaded', fn)
}

const range = size => [...Array(size).keys()]

const parseColor = hex => {
  const r = hex.substr(1, 2)
  const g = hex.substr(3, 2)
  const b = hex.substr(5, 2)

  return {
    r: parseInt(r, 16),
    g: parseInt(g, 16),
    b: parseInt(b, 16)
  }
}

onReady(async () => {
  const { bind, wire } = hyperHTML

  const grid = document.querySelector('#grid')
  const picker = document.querySelector('#picker')

  const tile = props => wire(props)`
    <div data-x="${props.x}" data-y="${props.y}" onClick=${props.onClick}>
    </div>`

  const onClick = event => {
    const { x, y } = event.target.dataset
    const { r, g, b } = parseColor(picker.value)

    console.log(`/update?x=${x}&y=${y}&r=${r}&g=${g}&b=${b}`)
    fetch(`/update?x=${x}&y=${y}&r=${r}&g=${g}&b=${b}`).then(response => {
      event.target.style.backgroundColor = picker.value
    })
  }

  const tiles = range(12).flatMap(y => {
    return range(12).map(x => {
      return tile({ x, y, onClick })
    })
  })

  bind(grid)`${tiles}`
})
