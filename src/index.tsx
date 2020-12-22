import { useLayoutEffect } from 'react'
import { NativeEventEmitter, NativeModules } from 'react-native'

const RNZebraScanner = new NativeEventEmitter(NativeModules.ZebraScanner)

type EventBarcode = {
  id: string
  barcode: string
  type: string
}

type EventBarcodeHandler = (barcode: string, scannerId: string) => void

const useZebraScanner = (onScan: EventBarcodeHandler) => {
  useLayoutEffect(() => {
    const handleEvent = (data: EventBarcode) => {
      if (onScan) {
        onScan(data.barcode || '', data.id)
      }
    }

    const listener = RNZebraScanner.addListener('scanner-barcode', handleEvent)
    return () => {
      listener.remove()
    }
  })
}

export default useZebraScanner
