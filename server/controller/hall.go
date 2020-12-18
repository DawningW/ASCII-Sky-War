package controller

import (
	"errors"
	"famehall/model"
	"famehall/model/reqo"
	"famehall/model/reso"

	"github.com/kataras/iris/v12"
)

// PostHall send hall
func PostHall(ctx iris.Context) {
	req := reqo.PostHall{}
	ctx.ReadJSON(&req)

	if req.Name == "" {
		ctx.JSON(model.ErrorVerification(errors.New("用户名为空")))
		return
	}

	if req.Score <= 0 {
		ctx.JSON(model.ErrorVerification(errors.New("分数值过大或小于等于零")))
		return
	}

	id, err := HallService.Insert(req.Name, req.Score)
	if err != nil {
		ctx.JSON(model.ErrorInsertDatabase(err))
		return
	}

	res := reso.PostHall{
		ID: id,
	}

	ctx.JSON(res)
}

// GetHall get all hall
func GetHall(ctx iris.Context) {
	req := reqo.GetHall{}
	ctx.ReadQuery(&req)

	scoreList, err := HallService.Query(req.ID, req.Name, req.Record)
	if err != nil {
		ctx.JSON(model.ErrorQueryDatabase(err))
		return
	}

	// Build response object
	resList := []reso.GetHall{}

	for _, score := range scoreList {
		// Get single res
		res := reso.GetHall{
			ID:    score.ID,
			Name:  score.Name,
			Score: score.Score,
			Time:  score.CreatedAt.Unix(),
			Rank:  score.Rank,
			Total: score.Total,
		}

		// Add into resList
		resList = append(resList, res)
	}

	ctx.Header("Access-Control-Allow-Origin", "*")
	ctx.JSON(resList)
}
