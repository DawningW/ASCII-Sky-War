package service

import (
	"famehall/config"
	"famehall/model/pojo"
	"strconv"
	"unsafe"

	"xorm.io/xorm"
)

// ScoreService Score service
type ScoreService struct {
	db *xorm.Engine
}

// Query query Score by ID / name
func (service *ScoreService) Query(ID int64, name string, record int64) ([]pojo.ScoreWithRank, error) {
	var IDList []int64
	var scoreList []pojo.Score
	var rankList []pojo.ScoreWithRank

	db := service.db.NewSession()
	defer db.Close()

	db.Begin()

	if ID > 0 {
		db = db.Where("score.id = ?", ID)
	}
	if name != "" {
		db = db.Where("score.name = ?", name)
	}

	db = db.Limit(config.Viper.GetInt("webpage.HallLimit"), int(record)).Desc("score.score")

	// Execute query
	if err := db.Table("score").Cols("score.id").Find(&IDList); err != nil {
		return nil, err
	}

	if len(IDList) <= 0 {
		return rankList, nil
	}

	if err := db.In("score.id", IDList).Desc("score.score").Find(&scoreList); err != nil {
		return nil, err
	}

	total, err := service.Total(db)
	if err != nil {
		return nil, err
	}

	queryPage := false
	if ID <= 0 && name == "" {
		queryPage = true
	}

	for i, score := range scoreList {
		var rank int64
		if queryPage {
			rank = int64(i+1) + record
		} else {
			r, err := service.Rank(score.Score, db)
			if err != nil {
				return nil, err
			}
			rank = r
		}
		rankList = append(rankList, pojo.ScoreWithRank{
			ID:        score.ID,
			Name:      score.Name,
			Score:     score.Score,
			Rank:      rank,
			Total:     total,
			CreatedAt: score.CreatedAt,
		})
	}
	db.Commit()

	return rankList, nil
}

// Insert insert Score and return insert id
func (service *ScoreService) Insert(name string, score int64) (int64, error) {
	obj := pojo.Score{
		Name:  name,
		Score: score,
	}

	// Execute insert
	if _, err := service.db.Insert(&obj); err != nil {
		return 0, err
	}

	return obj.ID, nil
}

func (service *ScoreService) Rank(score int64, session *xorm.Session) (int64, error) {
	var obj pojo.Score
	var db *xorm.Session

	if session == nil {
		db = service.db.NewSession()
		defer db.Close()
	} else {
		db = session
	}

	db.Where("score.score > ?", score)

	// Execute query
	n, err := db.Count(&obj)
	if err != nil {
		return 0, err
	}

	return n + 1, nil
}

func (service *ScoreService) Total(session *xorm.Session) (int64, error) {
	var db *xorm.Session

	if session == nil {
		db = service.db.NewSession()
		defer db.Close()
	} else {
		db = session
	}

	// Execute query
	result, err := db.Query("SELECT MAX(id)-MIN(id) FROM `score`")
	if err != nil {
		return 0, err
	}

	count := result[0]["MAX(id)-MIN(id)"]
	n, err := strconv.ParseInt(*(*string)(unsafe.Pointer(&count)), 10, 64)
	if err != nil {
		return 0, err
	}

	return n + 1, nil
}
