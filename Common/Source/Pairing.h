/* (C) Tokyo Cosmos Electric, Inc. (TOCOS) - 2015 all rights reserved.
 *
 * Condition to use: (refer to detailed conditions in Japanese)
 *   - The full or part of source code is limited to use for TWE (TOCOS
 *     Wireless Engine) as compiled and flash programmed.
 *   - The full or part of source code is prohibited to distribute without
 *     permission from TOCOS.
 *
 * 利用条件:
 *   - 本ソースコードは、別途ソースコードライセンス記述が無い限り東京コスモス電機が著作権を
 *     保有しています。
 *   - 本ソースコードは、無保証・無サポートです。本ソースコードや生成物を用いたいかなる損害
 *     についても東京コスモス電機は保証致しません。不具合等の報告は歓迎いたします。
 *   - 本ソースコードは、東京コスモス電機が販売する TWE シリーズ上で実行する前提で公開
 *     しています。他のマイコン等への移植・流用は一部であっても出来ません。
 *
 ****************************************************************************/

#ifndef PAIR_CONFIG_H_
#define PAIR_CONFIG_H_

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/
#define PAIR_ID			APP_ID+3
#define PAIR_CHANNEL	25

#define PAIR_LED_NOUSE 0xFF

#define PAIRING_PARENT 0x01
#define PAIRING_CHILD 0x02

/**
 * アプリケーションごとの振る舞いを決める関数テーブル
 */
typedef struct _sCbHandlerPair {
	uint8 (*pf_cbToCoNet_u8HwInt)(uint32 u32DeviceId, uint32 u32ItemBitmap);
	void (*pf_cbToCoNet_vHwEvent)(uint32 u32DeviceId, uint32 u32ItemBitmap);
	void (*pf_cbToCoNet_vMain)();
	void (*pf_cbToCoNet_vNwkEvent)(teEvent eEvent, uint32 u32arg);
	void (*pf_cbToCoNet_vRxEvent)(tsRxDataApp *pRx);
	void (*pf_cbToCoNet_vTxEvent)( uint8 u8CbId, uint8 bStatus );
} tsCbHandlerPair;

typedef struct _sPairingInfo{
	bool_t bStatus;					//!< Success -> TRUE, failure -> FALSE
	uint32 u32DstAddr;				//!< ペアリングした相手のアドレス
	uint32 u32PairKey;				//!< ペアリングした相手と共通の番号
	uint8* au8Data;					//!< 汎用的なデータ列
	uint8 u8DataLength;				//!< データ列のバイト数
	uint8 u8DataType;				//!< データ列の識別子
} tsPairingInfo;

typedef struct _sPairingConf{
	uint8 u8PairCh;					//!< ペアリングする際に使用するチャネル
	uint32 u32AppID;				//!< ペアリングする際に使用するAppID
	uint32 u32PairKey;				//!< ペアリング時の照合ID
	uint8 u8LEDPort;				//!< 状態表示用LEDのポート 19以上は点灯しない
	uint8 u8ThLQI;					//!< ペアリングする際のLQIの閾値
	uint8* au8Data;					//!< 汎用的なデータ列
	uint8 u8DataLength;				//!< データ列のバイト数
	uint8 u8DataType;				//!< データ列の識別子
	uint32 u32AppVer;				//!< アプリケーションのバージョン番号
	uint8 u8PairingMode;			//!< 0x01 : 最初から待ち受け 0x02 : 複数回送信 それ以外 : 最初にパケットを1回送信、その後応答がなければ待ち受け
	uint8 u8Retry;					//!< 送信リトライ回数
	uint32 u32ListenWait_ms;		//!< 受信待ち時間(ms)

	bool_t bDisableUART;			//!< Pairing中のUART出力を有効にする場合はFALSE、出力しない場合はTRUE
	tsFILE sSerStream;				//!< UART出力先
	void (*pf_cbSavePair)(tsPairingInfo *psPairingInfo);	//!< アドレスやアプリケーションIDを渡すコールバック関数ポインタ
} tsPairingConf;
/****************************************************************************/
/***        Exported Functions                                            ***/
/****************************************************************************/
void vInitAppPairing( tsPairingConf *psConfig );

/****************************************************************************/
/***        Exported Variables                                            ***/
/****************************************************************************/

extern void *pvProcessEvPair;
extern tsCbHandlerPair *psCbHandlerPair;

#endif /* PAIR_CONFIG_H_ */
