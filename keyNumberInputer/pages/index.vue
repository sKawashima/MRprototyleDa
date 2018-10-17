<template lang='pug'>
v-layout(column, justify-center, align-center)
  h2 Keyboard Input
  v-flex(xs12='', sm8='', md6='')
    p.mx-3.text-xs-center now octave: {{octave}}
    v-card.pa-3.ma-3
      p.ma-0 {{tones}}
    v-spacer
    v-card.pa-3.ma-3
      p.ma-0 {{toneNumbers}}
</template>

<script>
if (process.browser) {
  var Tone = require('tone')
}

var vm
var synth
const keys = ['a', 'w', 's', 'e', 'd', 'f', 't', 'g', 'y', 'h', 'u', 'j', 'k', 'o', 'l']
const frequencys = ['C', 'C#', 'D', 'D#', 'E', 'F', 'F#', 'G', 'G#', 'A', 'A#', 'B', 'C', 'C#', 'D']

export default {
  data: () => {
    return {
      tones: [],
      octave: 4,
      toneNumbers: []
    }
  },
  methods: {
    addInput: (input) => {
      console.log(input.key)
      if (input.key === 'Backspace') {
        vm.tones.pop()
        synth.triggerRelease()
        return
      } else if (input.key === 'x') {
        vm.octave++
        return
      } else if (input.key === 'z') {
        vm.octave--
        return
      }
      let r = -1
      keys.forEach((el, i) => {
        if (el === input.key) {
          r = i
          return 0 // out forEach
        }
      })
      if (r !== -1) { // toneKey
        if (r >= 12) { vm.octave++ }
        vm.tones.push(vm.keyboardToFrequency(r) + vm.octave)
        synth.triggerAttack(vm.keyboardToFrequency(r) + vm.octave)
        if (r >= 12) { vm.octave-- }
      } else {
        synth.triggerRelease()
      }
    },
    keyboardToFrequency: (i) => {
      return frequencys[i]
    }
  },
  watch: {
    tones: () => {
      vm.toneNumbers = vm.tones.map((tone) => {
        return (Tone.Frequency(tone).toMidi())
      })
    }
  },
  created () {
    if (process.browser) {
      console.log(Tone.Frequency('A3').toMidi())
      window.addEventListener('keydown', this.addInput, true)
      synth = new Tone.AMSynth().toMaster()
      synth.oscillator.type = 'sawtooth'
    }
    vm = this
    // console.log(this)
  }
}
</script>
