const app = getApp()

function inArray(arr, key, val) {
  for (let i = 0; i < arr.length; i++) {
    if (arr[i][key] === val) {
      return i;
    }
  }
  return -1;
}

// ArrayBuffer转16进度字符串示例
function ab2hex(buffer) {
  var hexArr = Array.prototype.map.call(
    new Uint8Array(buffer),
    function (bit) {
      return ('00' + bit.toString(16)).slice(-2)
    }
  )
  return hexArr.join('');
}



const defaultAvatarUrl = 'https://mmbiz.qpic.cn/mmbiz/icTdbqWNOwNRna42FI242Lcia07jQodd2FJGIYQfG0LAJGFxM4FbnQP6yfMxBgJ0F3YRqJCJ1aPAK2dQagdusBZg/0'

Page({
  data: {
    avatarUrl: defaultAvatarUrl,

    devices: [],
    connected: false,
    chs: [],
    canWrite:false,
    sendmsg:0
  },

  onChooseAvatar(e) {
    const { avatarUrl } = e.detail 
    this.setData({
      avatarUrl,
    })
  },
  onLoad: function (options) {
    this.checkSetting();
  },

  openBluetoothAdapter() {

    wx.openBluetoothAdapter({
      success: (res) => {
        console.log('openBluetoothAdapter success', res)
        this.startBluetoothDevicesDiscovery()
      },
      fail: (res) => {
        if (res.errCode === 10001) {
          wx.onBluetoothAdapterStateChange(function (res) {
            console.log('onBluetoothAdapterStateChange', res)
            if (res.available) {
              this.startBluetoothDevicesDiscovery()
            }
          })
        }
      }
    }),
    this.setData({
      canWrite: false
    }),
    console.log("adapter log")
  },
  getBluetoothAdapterState() {
    wx.getBluetoothAdapterState({
      success: (res) => {
        console.log('getBluetoothAdapterState', res)
        if (res.discovering) {
          this.onBluetoothDeviceFound()
        } else if (res.available) {
          this.startBluetoothDevicesDiscovery()
        }
      }
    })
  },
  onBluetoothDeviceFound() {
    
    wx.onBluetoothDeviceFound((res) => {
      
      res.devices.forEach(device => {
        if (!device.name && !device.localName) {
          return
        }
        const foundDevices = this.data.devices
        const idx = inArray(foundDevices, 'deviceId', device.deviceId)
        const data = {}
        if (idx === -1) {
          data[`devices[${foundDevices.length}]`] = device
        } else {
          data[`devices[${idx}]`] = device
        }
        this.setData(data)
      });

    })
  },
 
  startBluetoothDevicesDiscovery() {
    if (this._discoveryStarted) {
      return
    }
    this._discoveryStarted = true
    wx.startBluetoothDevicesDiscovery({
      allowDuplicatesKey: true,
      success: (res) => {
        console.log('startBluetoothDevicesDiscovery success', res)
        this.onBluetoothDeviceFound()
      },
    }).then((res) => {

    }).then(()=>{


    }).catch(err=>{
      console.log('蓝牙搜索失败',err);
      wx.showToast({
        title: '请检查蓝牙是否开启',
        icon:'none'
      })
    })

  },

  stopBluetoothDevicesDiscovery() {
    wx.stopBluetoothDevicesDiscovery()
  },

  createBLEConnection(e) {
    const ds = e.currentTarget.dataset
    const deviceId = ds.deviceId
    const name = ds.name
    wx.createBLEConnection({
      deviceId,
      success: (res) => {
        this.setData({
          connected: true,
          name,
          deviceId,
        })
        this.getBLEDeviceServices(deviceId)

      },
      fail:(res)=>{
        console.log(res.errMsg)
        console.error(res.errCode)
        if(res.errCode == -1)
        {
          this.setData({
            connected: true,
            name,
            deviceId,
            canWrite: true,
          })
        }
      }
    })
    this.stopBluetoothDevicesDiscovery()

  },
  closeBluetoothAdapter() {
    wx.closeBluetoothAdapter()
    this._discoveryStarted = false
  },

  closeBLEConnection() {
    // this.closeBluetoothAdapter();
    // this.openBluetoothAdapter();
    // wx.closeBLEConnection({

    //   deviceId: this.data.deviceId
    // })
    this.setData({
      connected: false,
      chs: [],
      canWrite: false,
    })
  },


  getBLEDeviceServices(deviceId) {
    wx.getBLEDeviceServices({
      deviceId,
      success: (res) => {
        for (let i = 0; i < res.services.length; i++) {
          if (res.services[i].isPrimary) {
            this.getBLEDeviceCharacteristics(deviceId, res.services[i].uuid)
            return
          }
        }
      }
    })
  },
  getBLEDeviceCharacteristics(deviceId, serviceId) {
    wx.getBLEDeviceCharacteristics({
      deviceId,
      serviceId,
      success: (res) => {
        console.log('getBLEDeviceCharacteristics success', res.characteristics)
        for (let i = 0; i < res.characteristics.length; i++) {
          let item = res.characteristics[i]
          if (item.properties.read) {
            wx.readBLECharacteristicValue({
              deviceId,
              serviceId,
              characteristicId: item.uuid,
            })
          }
          if (item.properties.write) {
            this.setData({
              canWrite: true
            })
            this._deviceId = deviceId
            this._serviceId = serviceId
            this._characteristicId = item.uuid
            this.writeBLECharacteristicValue()
          }
          if (item.properties.notify || item.properties.indicate) {
            wx.notifyBLECharacteristicValueChange({
              deviceId,
              serviceId,
              characteristicId: item.uuid,
              state: true,
            })
          }
        }
      },
      fail(res) {
        console.error('getBLEDeviceCharacteristics', res)
      }
    })
    // 操作之前先监听，保证第一时间获取数据
    wx.onBLECharacteristicValueChange((characteristic) => {
      const idx = inArray(this.data.chs, 'uuid', characteristic.characteristicId)
      const data = {}
      if (idx === -1) {
        data[`chs[${this.data.chs.length}]`] = {
          uuid: characteristic.characteristicId,
          value: ab2hex(characteristic.value)
        }
      } else {
        data[`chs[${idx}]`] = {
          uuid: characteristic.characteristicId,
          value: ab2hex(characteristic.value)
        }
      }
      // data[`chs[${this.data.chs.length}]`] = {
      //   uuid: characteristic.characteristicId,
      //   value: ab2hex(characteristic.value)
      // }
      this.setData(data)
    })
  },
//向蓝牙设备发送一个0x00的16进制数据
hexStringToArrayBuffer(str) {undefined
  if (!str) {
    undefined
  return new ArrayBuffer(0);
  }
  var buffer = new ArrayBuffer(str.length);
  let dataView = new DataView(buffer)
  let ind = 0;
  for (var i = 0, len = str.length; i < len; i += 2) {undefined
  let code = parseInt(str.substr(i, 2), 16)
  dataView.setUint8(ind, code)
  ind++
  }
  return buffer;
  },
  //字符串转16进制

  stringToBytes(str) {
    var array = new Uint8Array(str.length);
    for (var i = 0, l = str.length; i < l; i++) {
      array[i] = str.charCodeAt(i);
    }
    console.log(array);
    return array.buffer;
  },
  //字符串与16进制的转换
  ab2hex(buffer){
    var hexArr =Array.prototype.map.call(
      new Uint16Array(buffer),
      function(bit){
        return ('00'+bit.toString(16).slice(-2))
      }
    )
    return hexArr.join('');
  },

  writeBLECharacteristicValue() {
    // 向蓝牙设备发送一个0x00的16进制数据
    let buffer = new ArrayBuffer(1)
    let dataView = new DataView(buffer)
    dataView.setUint8(0, 0xaa)
    wx.writeBLECharacteristicValue({
      deviceId: this._deviceId,
      serviceId: this._serviceId,
      characteristicId: this._characteristicId,
      value: buffer,
    })
  },
  writeBLECharacteristicValue_Forward() {
    // 向蓝牙设备发送一个0x00的16进制数据
    
    // let buffer = new ArrayBuffer(1)
    // let dataView = new DataView(buffer)
    // dataView.setUint8(0, 0xaa)
    //let buffer2 =this.hexStringToArrayBuffer("AAAA20201015555")

    let buffer2 = new ArrayBuffer(20)
    buffer2 = this.stringToBytes("forward")

    wx.writeBLECharacteristicValue({
      deviceId: this._deviceId,
      serviceId: this._serviceId,
      characteristicId: this._characteristicId,
      value: buffer2,
    })
  },
  writeBLECharacteristicValue_Back() {
    // 向蓝牙设备发送一个0x00的16进制数据
    // let buffer = new ArrayBuffer(1)
    // let dataView = new DataView(buffer)
    // dataView.setUint8(0, 0xBB)
    let buffer2 = new ArrayBuffer(20)
    buffer2 = this.stringToBytes("back")
    wx.writeBLECharacteristicValue({
      deviceId: this._deviceId,
      serviceId: this._serviceId,
      characteristicId: this._characteristicId,
      value: buffer2,
    })
  },
  writeBLECharacteristicValue_TurnLeft() {
    // 向蓝牙设备发送一个0x00的16进制数据
    // let buffer = new ArrayBuffer(1)
    // let dataView = new DataView(buffer)
    // dataView.setUint8(0, 0xCC)
    let buffer2 = new ArrayBuffer(20)
    buffer2 = this.stringToBytes("turnleft")

    wx.writeBLECharacteristicValue({
      deviceId: this._deviceId,
      serviceId: this._serviceId,
      characteristicId: this._characteristicId,
      value: buffer2,
    })
  },
  writeBLECharacteristicValue_TurnRight() {
    // 向蓝牙设备发送一个0x00的16进制数据
    // let buffer = new ArrayBuffer(1)
    // let dataView = new DataView(buffer)
    // dataView.setUint8(0, 0xDD)

    let buffer2 = new ArrayBuffer(20)
    buffer2 = this.stringToBytes("turnright")
    wx.writeBLECharacteristicValue({
      deviceId: this._deviceId,
      serviceId: this._serviceId,
      characteristicId: this._characteristicId,
      value: buffer2,
    })
  },
  writeBLECharacteristicValue_Stop() {
    // 向蓝牙设备发送一个0x00的16进制数据
    // let buffer = new ArrayBuffer(1)
    // let dataView = new DataView(buffer)
    // dataView.setUint8(0, 0xFF)
    let buffer2 = new ArrayBuffer(20)
    buffer2 = this.stringToBytes("stop")
    wx.writeBLECharacteristicValue({
      deviceId: this._deviceId,
      serviceId: this._serviceId,
      characteristicId: this._characteristicId,
      value: buffer2,
    })
  },

  checkSetting(){
    // 可以通过 wx.getSetting 先查询一下用户是否授权了 "scope.bluetooth" 这个 scope
    wx.getSetting({
      success(res) {
        console.log(res.authSetting)
        //判断是否有'scope.bluetooth'属性
        if (res.authSetting.hasOwnProperty('scope.bluetooth')) {
          //'scope.bluetooth'属性存在，且为false
          if (!res.authSetting['scope.bluetooth']) {
            //弹窗授权
            wx.openSetting({
              success(res) {
                console.log(res.authSetting)
              }
            })
          }
        }
        else
          //'scope.bluetooth'属性不存在，需要授权
          wx.authorize({
            scope: 'scope.bluetooth',
            success() {
              // 用户已经同意小程序使用手机蓝牙功能，后续调用 蓝牙 接口不会弹窗询问
              console.log(res.authSetting)
            }
          })
      }
    })
  },
})
