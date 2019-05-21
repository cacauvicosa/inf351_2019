/*! Author: Raphael Nepomuceno <raphael@nepomuceno.dev> */

const onReady = fn => {
  if (document.readyState !== 'loading') fn()
  else document.addEventListener('DOMContentLoaded', fn)
}
