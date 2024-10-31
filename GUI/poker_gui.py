import tkinter as tk
from tkinter import Canvas, Label, Entry, Button

def create_rounded_rectangle(canvas, x1, y1, x2, y2, radius=25, **kwargs):
    """Draws a rounded rectangle on the canvas"""
    points = [
        x1+radius, y1,
        x1+radius, y1,
        x2-radius, y1,
        x2-radius, y1,
        x2, y1,
        x2, y1+radius,
        x2, y1+radius,
        x2, y2-radius,
        x2, y2-radius,
        x2, y2,
        x2-radius, y2,
        x2-radius, y2,
        x1+radius, y2,
        x1+radius, y2,
        x1, y2,
        x1, y2-radius,
        x1, y2-radius,
        x1, y1+radius,
        x1, y1+radius,
        x1, y1
    ]
    return canvas.create_polygon(points, **kwargs, smooth=True)

# Initialize main window
root = tk.Tk()

root.title("Poker GUI")
root.geometry("900x500")
root.configure(bg="silver")

# Create a canvas to draw the board and cards
canvas = Canvas(root,width=600, height=400, bg="darkgreen")
canvas.pack()

# Define the card placement coordinates

card_width = 70
card_height = 100
card_spacing = 10
board_start_x = (600 - 5 * card_width - 4 * card_spacing)/2
board_start_y = 150

# Draw placeholders for five board cards (community cards)
board_cards = []
for i in range(5):
    x = board_start_x + i * (card_width + card_spacing)
    y = board_start_y
    card = create_rounded_rectangle(canvas, x, y, x + card_width, y + card_height, radius=15, outline="white", width=2)
    board_cards.append(card)

# Draw placeholders for hero's hole cards
hero_start_x = board_start_x + card_width * 1.5 + card_spacing
hero_start_y = 430 - 3 * card_height/2
hero_cards = []
for i in range(2):
    x = hero_start_x + i * (card_width + card_spacing)
    card = create_rounded_rectangle(canvas, x, hero_start_y, x + card_width, hero_start_y + card_height, radius=15, outline="white", width=2)
    hero_cards.append(card)

# Draw placeholders for villain's hole cards
villain_start_x = hero_start_x
villain_start_y = 20
villain_cards = []
for i in range(2):
    x = villain_start_x + i * (card_width + card_spacing)
    card = create_rounded_rectangle(canvas, x, villain_start_y, x + card_width, villain_start_y + card_height, radius=15, outline="white", width=2)
    villain_cards.append(card)

# Stack size fields
hero_stack_label = Label(root, text="Hero Stack ($):", bg="green", fg="white")
hero_stack_label.place(x=hero_start_x - 45, y=hero_start_y + 20)
hero_stack_entry = Entry(root, width=8)
hero_stack_entry.place(x=hero_start_x - 45, y=hero_start_y + 40)

villain_stack_label = Label(root, text="Villain Stack ($):", bg="green", fg="white")
villain_stack_label.place(x=villain_start_x - 45, y=villain_start_y + 20)
villain_stack_entry = Entry(root, width=8)
villain_stack_entry.place(x=villain_start_x - 45, y=villain_start_y + 40)

# Action buttons for hero (bottom side)
hero_call_button = Button(root, text="Call", width=8)
hero_call_button.place(x=hero_start_x + 2*card_width+card_spacing+200, y=hero_start_y + 20)
hero_raise_button = Button(root, text="Raise", width=8)
hero_raise_button.place(x=hero_start_x + 2*card_width+card_spacing+200, y=hero_start_y + 50)
hero_fold_button = Button(root, text="Fold", width=8)
hero_fold_button.place(x=hero_start_x + 2*card_width+card_spacing+200, y=hero_start_y + 80)

# Action buttons for villain (top side)
villain_call_button = Button(root, text="Call", width=8)
villain_call_button.place(x=villain_start_x + 2*card_width+card_spacing+200, y=villain_start_y)
villain_raise_button = Button(root, text="Raise", width=8)
villain_raise_button.place(x=villain_start_x + 2*card_width+card_spacing+200, y=villain_start_y + 30)
villain_fold_button = Button(root, text="Fold", width=8)
villain_fold_button.place(x=villain_start_x + 2*card_width+card_spacing+200, y=villain_start_y + 60)
# Run the main loop
root.mainloop()
