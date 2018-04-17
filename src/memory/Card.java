/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package memory;

import java.awt.Button;
import java.awt.Color;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Date;

/**
 *
 * @author Laiman
 */
public class Card extends Button{
   private final Color frontColor = Color.gray;
   private Color backColor = generateRandomColor();
   private boolean isMatched = false;
   private ArrayList<ICardListener> clickListeners = new ArrayList<>();
   
   
   public Card(String label){
        super(label);
        this.setBackground(frontColor);
       
        addMouseListener(new MouseAdapter(){
                    @Override
                    public void mouseClicked(MouseEvent e){
                        if(isMatched == false){
                            for(ICardListener clickListener: clickListeners){
                                try {
                                    clickListener.cardClicked((Card)e.getSource());
                                } catch (IOException e1) {
                                    e1.printStackTrace();
                                }
                            }
                        }
                    }
                });
    }
   
   private Color generateRandomColor(){
       Random rand = new Random();
       
       float r = rand.nextFloat();
       float g = rand.nextFloat();
       float b = rand.nextFloat();
       
       Color randomColor = new Color(r, g, b);
       return randomColor;
   }
   
   public Color getCardColor(){
        return backColor;
   }
   
   public void setCardColor(Color newColor){
       this.backColor = newColor;
   }
   
   public Color getFrontColor(){
        return frontColor;
   }
   
   public void setMatched(boolean matchOrNot){
       isMatched = matchOrNot;
   }
   
   public boolean getMatched(){
       return isMatched;
   }
   
   public boolean isFilped(){
       return (this.getBackground().equals(this.getCardColor()));
   }
   
   public void addCardClickedListener(ICardListener listener){
       clickListeners.add(listener);
   }
}