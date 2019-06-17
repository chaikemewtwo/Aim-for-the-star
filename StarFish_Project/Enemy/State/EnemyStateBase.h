#pragma once

class EnemyBase;

// 状態基底クラス
class StateBase {
public:
	virtual void Action(EnemyBase* e) = 0;
	virtual ~StateBase() {}
};
/*
＊Stateについての考え
　　Stateごとに基底を作る。そこで処理を定義する。
  　StateBase→各StateBase→各Stateの順。
　　EnemyBaseから変数を各StateBaseに渡して挙動処理を記述。
  　各Stateはその処理を呼び出し、遷移のためのif文を記述。
*/