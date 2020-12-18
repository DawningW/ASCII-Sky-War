package pojo

import "time"

// Score 消息实体，对应表Score
type Score struct {
	ID        int64
	Name      string    `xorm:"notnull"`
	Score     int64     `xorm:"notnull index(rank)"`
	CreatedAt time.Time `xorm:"created"` // 这个Field将在Insert时自动赋值为当前时间
}

type ScoreWithRank struct {
	ID        int64
	Name      string
	Score     int64
	Rank      int64
	Total     int64
	CreatedAt time.Time
}
