<template lang='pug'>
v-app(dark)
  v-navigation-drawer(:mini-variant='miniVariant', :clipped='clipped', v-model='drawer', fixed='', app='')
    v-list
      v-list-tile(router='', :to='item.to', :key='i', v-for='(item, i) in items', exact='')
        v-list-tile-action
          v-icon(v-html='item.icon')
        v-list-tile-content
          v-list-tile-title(v-text='item.title')
  v-toolbar(fixed='', app='', :clipped-left='clipped')
    v-toolbar-side-icon(@click='drawer = !drawer')
    //- v-btn(icon='', @click.stop='miniVariant = !miniVariant')
    //-   v-icon(v-html="miniVariant ? 'chevron_right' : 'chevron_left'")
    //- v-btn(icon='', @click.stop='clipped = !clipped')
    //-   v-icon web
    //- v-btn(icon='', @click.stop='fixed = !fixed')
    //-   v-icon remove
    v-toolbar-title(v-text='title')
    v-spacer
    //- v-btn(icon='', @click.stop='rightDrawer = !rightDrawer')
    //-   v-icon menu
  v-content
    v-container
      nuxt
  //- v-navigation-drawer(temporary='', :right='right', v-model='rightDrawer', fixed='')
  //-   v-list
  //-     v-list-tile(@click.native='right = !right')
  //-       v-list-tile-action
  //-         v-icon(light='') compare_arrows
  //-       v-list-tile-title Switch drawer (click me)
  v-footer(:fixed='fixed', app='')
    v-spacer
    span © 2018 sKawashima
    v-spacer
</template>

<script>
export default {
  data () {
    return {
      clipped: false,
      drawer: false,
      fixed: false,
      items: [
        { icon: 'keyboard', title: 'Keyboard Input', to: '/' },
        { icon: 'cloud_upload', title: 'SMF Input', to: '/fileInput' }
      ],
      miniVariant: false,
      right: true,
      rightDrawer: false,
      title: 'Key-Number Inputer'
    }
  }
}
</script>
